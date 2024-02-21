import os
from tqdm import tqdm
from PIL import Image
from deeplab import DeeplabV3

if __name__ == "__main__":
    deeplab = DeeplabV3()
    test_interval = 65
    dir_origin_path = "img/"
    dir_mask_path = "mask_out/"

    img_names = os.listdir(dir_origin_path)
    for img_name in tqdm(img_names):
        if img_name.lower().endswith(('.png','.jpg')):
            image_path = os.path.join(dir_origin_path, img_name)
            image = Image.open(image_path)
            r_image = deeplab.detect_image(image)
            if not os.path.exists(dir_mask_path):
                os.makedirs(dir_mask_path)

            mask_image_path = os.path.join(dir_mask_path, img_name)
            r_image.save(mask_image_path)