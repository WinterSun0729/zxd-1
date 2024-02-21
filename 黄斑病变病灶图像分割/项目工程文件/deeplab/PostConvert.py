import os
import numpy as np
from PIL import Image
from tqdm import tqdm

# 原始标签所在的路径
Origin_SegmentationClass_path = "./cmp"
# 输出标签所在的路径
Out_SegmentationClass_path = "./cmp_finish"

# 原始标签所在的路径
Origin_SegmentationClass_path2 = "./mask_out"
# 输出标签所在的路径
Out_SegmentationClass_path2 = "./mask_finish"

def convert_to_binary(input_folder, output_folder):
    # Ensure the output folder exists
    if not os.path.exists(output_folder):
        os.makedirs(output_folder)

    # Get all image files in the input folder
    image_files = [f for f in os.listdir(input_folder) if f.endswith(".png")]

    for image_file in image_files:
        # Construct the full file paths
        input_path = os.path.join(input_folder, image_file)
        output_path = os.path.join(output_folder, f"{image_file}")

        # Open the image file
        image = Image.open(input_path)

        # Convert the image to grayscale
        grayscale_image = image.convert("L")

        # Set a threshold to convert pixels to 0 or 1
        threshold = 128
        binary_image = grayscale_image.point(lambda p: p > threshold and 1)

        # Save the binary image
        binary_image.save(output_path)

        # Convert binary image to a NumPy array for counting
        binary_array = np.array(binary_image)

        # Count 0 and 1 pixels using NumPy
        zeros = np.count_nonzero(binary_array == 0)
        ones = np.count_nonzero(binary_array == 1)

# 调用函数进行转换
convert_to_binary(Origin_SegmentationClass_path, Out_SegmentationClass_path)
convert_to_binary(Origin_SegmentationClass_path2, Out_SegmentationClass_path2)

