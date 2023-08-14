# Luiz Fernando Rabelo - 11796893 - SCC0251 - Assignment 1: Enhancement and Super Resolution

import imageio as iio
import numpy as np

LOW_RESOLUTION_COUNT = 4    # number of low resolution input images to compose the high resolution one
HIST_LEVELS = 256           # number of intensity levels ("range of pixels") present in the images

NO_ENHANCEMENT = 0          # no enhancement is applied to the images
SINGLE_CUMULATIVE_HIST = 1  # each image is equalized considering its corresponding cumulative histogram
JOINT_CUMULATIVE_HIST = 2   # each image is equalized considering the cumulative histogram of all images
GAMMA_CORRECTION = 3        # a pixelwise gamma correction is applied to each image

def read_input_params() -> dict:
    params = {}
    params['low_base_name'] = input()
    params['high_name'] = input()
    params['enhancement_id'] = int(input())
    params['gamma'] = float(input())
    return params

def read_low_resolution_images(base_name: str) -> list:
    images = []
    for i in range(LOW_RESOLUTION_COUNT):
        images.append(iio.imread(base_name + str(i) + '.png'))
    return images

def apply_enhancement_method(low_images: list, enhancement_id: int, gamma: float) -> list:
    if enhancement_id == SINGLE_CUMULATIVE_HIST:
        return equalize_images_with_single_histogram(low_images[:])
    if enhancement_id == JOINT_CUMULATIVE_HIST:
        return equalize_images_with_joint_histogram(low_images[:])
    if enhancement_id == GAMMA_CORRECTION:
        return make_gamma_correction(low_images[:], gamma)
    return low_images[:]

def equalize_images_with_single_histogram(low_images: list) -> list:
    equalized_images = []
    for image in low_images:
        hist = build_histogram(image)
        cumulative_hist = np.zeros(HIST_LEVELS).astype(int)
        cumulative_hist[0] = hist[0]
        for i in range(1, HIST_LEVELS):
            cumulative_hist[i] = hist[i] + cumulative_hist[i-1]
        height, width = image.shape
        equalized_image = np.zeros((height,width)).astype(np.uint8)
        for level in range(HIST_LEVELS):
            new_value = ((HIST_LEVELS-1) / float(height*width)) * cumulative_hist[level]
            equalized_image[np.where(image == level)] = new_value
        equalized_images.append(equalized_image)
    return equalized_images

def equalize_images_with_joint_histogram(low_images: list) -> list:
    hist = np.zeros(HIST_LEVELS).astype(int)
    for image in low_images:
        hist += build_histogram(image)
    cumulative_hist = np.zeros(HIST_LEVELS).astype(int)
    cumulative_hist[0] = hist[0]
    for i in range(1, HIST_LEVELS):
        cumulative_hist[i] = hist[i] + cumulative_hist[i-1]
    equalized_images = []
    for image in low_images:
        height, width = image.shape
        equalized_image = np.zeros((height,width)).astype(np.uint8)
        for level in range(HIST_LEVELS):
            new_value = ((HIST_LEVELS-1) / float(height*width*4)) * cumulative_hist[level]
            equalized_image[np.where(image == level)] = new_value
        equalized_images.append(equalized_image)
    return equalized_images

def build_histogram(image: np.ndarray) -> np.ndarray:
    hist = np.zeros(HIST_LEVELS).astype(int)
    for level in range(HIST_LEVELS):
        pixels_count = np.sum(image == level)
        hist[level] = pixels_count
    return hist

def make_gamma_correction(low_images: list, gamma: float) -> list:
    corrected_images = []
    for image in low_images:
        height, width = image.shape
        for i in range(height):
            for j in range(width):
                image[i][j] = np.floor(255 * ((float(image[i][j]) / 255) ** (1 / gamma)))
        corrected_images.append(image)
    return np.array(corrected_images)

def compose_super_resolution_img(low_images: list) -> np.ndarray:
    height, width = low_images[0].shape
    super_image = []
    for i in range(height):
        for offset in [0,2]:
            row = []
            for j in range(width):
                row.append(low_images[offset][i][j])
                row.append(low_images[offset+1][i][j])
            super_image.append(np.array(row))
    return np.array(super_image)

def evaluate_rmse(high_image: np.ndarray, composed_image: np.ndarray) -> float:
    height, width = high_image.shape
    sum = 0
    for i in range(height):
        for j in range(width):
           sum += (int(high_image[i][j]) - int(composed_image[i][j])) ** 2
    return np.sqrt(sum / (height * width))

def main():
    params = read_input_params()
    low_images = read_low_resolution_images(params['low_base_name'])
    enhanced_images = apply_enhancement_method(low_images, params['enhancement_id'], params['gamma'])
    composed_image = compose_super_resolution_img(enhanced_images)
    high_image = iio.imread(params['high_name'])
    rmse = evaluate_rmse(high_image, composed_image)
    print(np.round(rmse, 4))
    
if __name__ == '__main__':
    main()
