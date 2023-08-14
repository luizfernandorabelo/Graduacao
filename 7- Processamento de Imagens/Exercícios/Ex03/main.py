# Luiz Fernando Rabelo - 11796893 - SCC0251 - Assignment 3: Image Descriptors

import numpy as np
import imageio as iio
from scipy import ndimage

X, Y = 0, 1         # gradient directions
R, G, B = 0, 1, 2   # red, green, blue levels

def read_image_list(img_names: list) -> list:
    return [convert_to_gray_level(iio.imread(name)) for name in img_names]

def convert_to_gray_level(img: np.ndarray) -> np.ndarray:
    return img[..., R] * 0.299 + img[..., G] * 0.587 + img[..., B] * .114

def evaluate_gradient(img: np.ndarray) -> np.ndarray:
    sobel_x = np.array([[-1, -2, -1], [0, 0, 0], [1, 2, 1]])
    sobel_y = np.array([[-1, 0, 1], [-2, 0, 2], [-1, 0, 1]])
    return (ndimage.convolve(img, sobel_x), ndimage.convolve(img, sobel_y))

def extract_magnitudes_from_gradient(gradient: tuple) -> np.ndarray:
    magnitudes = np.sqrt(np.square(gradient[X]) + np.square(gradient[Y]))
    return magnitudes / np.sum(magnitudes)

def extract_angle_bins_from_gradient(gradient: tuple) -> np.ndarray:
    return np.degrees(np.arctan(gradient[Y] / gradient[X]) + np.pi / 2) // 20
            
def build_hog_descriptors(imgs: list) -> list:
    descriptors = []
    for img in imgs:
        gradient = evaluate_gradient(img)
        magnitudes = extract_magnitudes_from_gradient(gradient)
        bins = extract_angle_bins_from_gradient(gradient)
        descriptors.append(np.array([sum(magnitudes[np.where(bins == i)]) for i in range(9)]))
    return descriptors

def print_predicted_classes_by_knn(descriptors: dict) -> None:
    for i in range(len(descriptors['testing'])):
        without_distances = build_sorted_descriptors_distances(descriptors['without_humans'], descriptors['testing'][i])
        with_distances = build_sorted_descriptors_distances(descriptors['with_humans'], descriptors['testing'][i])
        j = k = 0
        for _ in range(3):
            if without_distances[j] <= with_distances[k]:
                j += 1
            else:
                k += 1
        print('0 ', end='') if j > k else print('1 ', end='')
    print()
        
def build_sorted_descriptors_distances(descriptors: list, testing: np.ndarray) -> list:
    return sorted([np.sqrt(np.sum(np.square((d - testing)))) for d in descriptors])

def main():
    np.seterr(divide='ignore', invalid='ignore')
    labels = ['without_humans', 'with_humans', 'testing']
    descriptors = {}
    for label in labels:
        image_list = read_image_list(input().strip().split(' '))
        descriptors[label] = build_hog_descriptors(image_list)
    print_predicted_classes_by_knn(descriptors)

if __name__ == '__main__':
    main()
    