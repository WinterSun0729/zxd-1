import os

import numpy as np
from PIL import Image
from tqdm import tqdm

Origin_SegmentationClass_path   = "datasets/before"
Out_SegmentationClass_path      = "datasets/SegmentationClass"

Origin_Point_Value              = np.array([0, 255])
Out_Point_Value                 = np.array([0, 1])

if __name__ == "__main__":
    if not os.path.exists(Out_SegmentationClass_path):
        os.makedirs(Out_SegmentationClass_path)

    png_names = os.listdir(Origin_SegmentationClass_path)

    for png_name in tqdm(png_names):
        png     = Image.open(os.path.join(Origin_SegmentationClass_path, png_name))
        w, h    = png.size
        
        png     = np.array(png)
        out_png = np.zeros([h, w])
        for i in range(len(Origin_Point_Value)):
            mask = png[:, :] == Origin_Point_Value[i]
            if len(np.shape(mask)) > 2:
                mask = mask.all(-1)
            out_png[mask] = Out_Point_Value[i]
        
        out_png = Image.fromarray(np.array(out_png, np.uint8))
        out_png.save(os.path.join(Out_SegmentationClass_path, png_name))

    classes_nums        = np.zeros([256], np.int)
    for png_name in tqdm(png_names):
        png_file_name   = os.path.join(Out_SegmentationClass_path, png_name)
        if not os.path.exists(png_file_name):
            raise ValueError("error:path"%(png_file_name))
        
        png             = np.array(Image.open(png_file_name), np.uint8)
        classes_nums    += np.bincount(np.reshape(png, [-1]), minlength=256)