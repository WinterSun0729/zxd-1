import datetime
import os
from functools import partial
import numpy as np
import torch
import torch.backends.cudnn as cudnn
import torch.distributed as dist
import torch.optim as optim
from torch.utils.data import DataLoader
from nets.deeplabv3_plus import DeepLab
from nets.deeplabv3_training import get_lr_scheduler, set_optimizer_lr, weights_init
from utils.callbacks import EvalCallback, LossHistory
from utils.dataloader import DeeplabDataset, deeplab_dataset_collate
from utils.utils import download_weights, seed_everything, show_config, worker_init_fn
from utils.utils_fit import fit_one_epoch

if __name__ == "__main__":
    Cuda = True
    seed = 11
    num_classes = 3
    backbone = "mobilenet"
    model_path = "logs/last_epoch_weights.pth"
    downsample_factor = 8
    input_shape = [800, 800]
    Init_Epoch = 0
    def_Epoch = 200
    def_batch_size = 2
    Init_lr = 5e-4
    Min_lr = Init_lr * 0.00001
    optimizer_type = "adam"
    momentum = 0.9
    weight_decay = 0
    lr_decay_type = 'cos'
    save_period = 5
    save_dir = 'logs'
    eval_flag = True
    eval_period = 5
    datapath = 'datasets'
    dice_loss = True
    cls_weights = np.ones([num_classes], np.float32)
    num_workers = 4
    seed_everything(seed)
    ngpus_per_node = torch.cuda.device_count()
    device = torch.device('cuda' if torch.cuda.is_available() else 'cpu')
    local_rank = 0
    rank = 0

    model = DeepLab(num_classes=num_classes, backbone=backbone, downsample_factor=downsample_factor, pretrained=False)
    weights_init(model)
    if model_path != '':
        model_dict = model.state_dict()
        pretrained_dict = torch.load(model_path, map_location=device)
        load_key, no_load_key, temp_dict = [], [], {}
        for k, v in pretrained_dict.items():
            if k in model_dict.keys() and np.shape(model_dict[k]) == np.shape(v):
                temp_dict[k] = v
                load_key.append(k)
            else:
                no_load_key.append(k)
        model_dict.update(temp_dict)
        model.load_state_dict(model_dict)

    if local_rank == 0:
        time_str = datetime.datetime.strftime(datetime.datetime.now(), '%Y_%m_%d_%H_%M_%S')
        log_dir = os.path.join(save_dir, "loss_" + str(time_str))
        loss_history = LossHistory(log_dir, model, input_shape=input_shape)
    else:
        loss_history = None

    scaler = None

    model_train = model.train()

    if Cuda:
        model_train = torch.nn.DataParallel(model)

        cudnn.benchmark = True
        model_train = model_train.cuda()

    with open(os.path.join(datapath, "ImageSets/Segmentation/train.txt"), "r") as f:
        train_lines = f.readlines()
    with open(os.path.join(datapath, "ImageSets/Segmentation/val.txt"), "r") as f:
        val_lines = f.readlines()
    num_train = len(train_lines)
    num_val = len(val_lines)

    if local_rank == 0:
        wanted_step = 1.5e4 if optimizer_type == "sgd" else 0.5e4
        total_step = num_train // def_batch_size * def_Epoch
        if total_step <= wanted_step:
            if num_train // def_batch_size == 0:
                raise ValueError('数据集过小，无法进行训练，请扩充数据集。')
            wanted_epoch = wanted_step // (num_train // def_batch_size) + 1

    if True:
        batch_size = def_batch_size
        nbs = 16
        lr_limit_max = 5e-4 if optimizer_type == 'adam' else 1e-1
        lr_limit_min = 3e-4 if optimizer_type == 'adam' else 5e-4
        if backbone == "xception":
            lr_limit_max = 1e-4 if optimizer_type == 'adam' else 1e-1
            lr_limit_min = 1e-4 if optimizer_type == 'adam' else 5e-4
        Init_lr_fit = min(max(batch_size / nbs * Init_lr, lr_limit_min), lr_limit_max)
        Min_lr_fit = min(max(batch_size / nbs * Min_lr, lr_limit_min * 1e-2), lr_limit_max * 1e-2)
        optimizer = {
            'adam': optim.Adam(model.parameters(), Init_lr_fit, betas=(momentum, 0.999), weight_decay=weight_decay),
            'sgd': optim.SGD(model.parameters(), Init_lr_fit, momentum=momentum, nesterov=True, weight_decay=weight_decay)
        }[optimizer_type]
        lr_scheduler_func = get_lr_scheduler(lr_decay_type, Init_lr_fit, Min_lr_fit, def_Epoch)
        epoch_step = num_train // batch_size
        epoch_step_val = num_val // batch_size
        if epoch_step == 0 or epoch_step_val == 0:
            raise ValueError("数据集过小，无法继续进行训练，请扩充数据集。")
        train_dataset = DeeplabDataset(train_lines, input_shape, num_classes, True, datapath)
        val_dataset = DeeplabDataset(val_lines, input_shape, num_classes, False, datapath)
        train_sampler = None
        val_sampler = None
        shuffle = True
        gen = DataLoader(train_dataset, shuffle=shuffle, batch_size=batch_size, num_workers=num_workers, pin_memory=True,
                        drop_last=True, collate_fn=deeplab_dataset_collate, sampler=train_sampler,
                        worker_init_fn=partial(worker_init_fn, rank=rank, seed=seed))
        gen_val = DataLoader(val_dataset, shuffle=shuffle, batch_size=batch_size, num_workers=num_workers, pin_memory=True,
                            drop_last=True, collate_fn=deeplab_dataset_collate, sampler=val_sampler,
                            worker_init_fn=partial(worker_init_fn, rank=rank, seed=seed))
        if local_rank == 0:
            eval_callback = EvalCallback(model, input_shape, num_classes, val_lines, datapath, log_dir, Cuda, \
                                        eval_flag=eval_flag, period=eval_period)
        else:
            eval_callback = None
        for epoch in range(Init_Epoch, def_Epoch):
            set_optimizer_lr(optimizer, lr_scheduler_func, epoch)
            fit_one_epoch(model_train, model, loss_history, eval_callback, optimizer, epoch,
                        epoch_step, epoch_step_val, gen, gen_val, def_Epoch, Cuda, dice_loss, False,
                        cls_weights, num_classes, False, scaler, save_period, save_dir, local_rank)

    if local_rank == 0:
        loss_history.writer.close()
