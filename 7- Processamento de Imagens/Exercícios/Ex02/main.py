# Luiz Fernando Rabelo - 11796893 - SCC0251 - Assignment 2: Fourier Transform

import imageio as iio
import numpy as np

# Filter ids:
IDEAL_LOW_PASS = 0
IDEAL_HIGH_PASS = 1
IDEAL_BAND_PASS = 2
LAPLACIAN_HIGH_PASS = 3
GAUSSIAN_LOW_PASS = 4
BUTTERWORTH_LOW_PASS = 5
BUTTERWORTH_HIGH_PASS = 6
BUTTERWORTH_BAND_REJECT = 7
BUTTERWORTH_BAND_PASS = 8

def read_input_params() -> dict:
    params = {}
    params['input_name'] = input().strip()
    params['output_name'] = input().strip()
    params['filter_id'] = int(input())
    if params['filter_id'] in [IDEAL_LOW_PASS, IDEAL_HIGH_PASS]:
        params['r'] = float(input())
    elif params['filter_id'] == IDEAL_BAND_PASS:
        params['r1'] = float(input())
        params['r2'] = float(input())
    elif params['filter_id'] == GAUSSIAN_LOW_PASS:
        params['s1'] = float(input())
        params['s2'] = float(input())
    elif params['filter_id'] in [BUTTERWORTH_LOW_PASS, BUTTERWORTH_HIGH_PASS]:
        params['d0'] = float(input())
        params['n'] = float(input())
    elif params['filter_id'] in [BUTTERWORTH_BAND_REJECT, BUTTERWORTH_BAND_PASS]:
        params['d0'] = float(input())
        params['n0'] = float(input())
        params['d1'] = float(input())
        params['n1'] = float(input())
    return params

def apply_frequency_filter(transform: np.ndarray, params: dict) -> np.ndarray:
    if params['filter_id'] == IDEAL_LOW_PASS:
        filter = build_ideal_lowpass_filter(transform, params['r'])
    elif params['filter_id'] == IDEAL_HIGH_PASS:
        filter = build_ideal_highpass_filter(transform, params['r'])
    elif params['filter_id'] == IDEAL_BAND_PASS:
        hp_filter1 = build_ideal_highpass_filter(transform, params['r1'])
        hp_filter2 = build_ideal_highpass_filter(transform, params['r2'])
        filter = hp_filter2 - hp_filter1
    elif params['filter_id'] == LAPLACIAN_HIGH_PASS:
        filter = build_laplacian_highpass_filter(transform)
    elif params['filter_id'] == GAUSSIAN_LOW_PASS:
        filter = build_gaussian_lowpass_filter(transform, params['s1'], params['s2'])
    elif params['filter_id'] == BUTTERWORTH_LOW_PASS:
        filter = build_butterworth_lowpass_filter(transform, params['d0'], params['n'])
    elif params['filter_id'] == BUTTERWORTH_HIGH_PASS:
        filter = build_butterworth_highpass_filter(transform, params['d0'], params['n'])
    elif params['filter_id'] == BUTTERWORTH_BAND_REJECT:
        hp_filter1 = build_butterworth_highpass_filter(transform, params['d0'], params['n0'])
        hp_filter2 = build_butterworth_highpass_filter(transform, params['d1'], params['n1'])
        filter = hp_filter1 - hp_filter2
    elif params['filter_id'] == BUTTERWORTH_BAND_PASS:
        hp_filter1 = build_butterworth_highpass_filter(transform, params['d0'], params['n0'])
        hp_filter2 = build_butterworth_highpass_filter(transform, params['d1'], params['n1'])
        filter = hp_filter2 - hp_filter1
    else:
        filter = np.fft.ifft2(np.fft.ifftshift(transform)).real
    return normalize_image(filter).astype(np.uint8)
        
def build_ideal_lowpass_filter(transform: np.ndarray, r: float) -> np.ndarray:
    height, width = transform.shape
    filter = np.zeros((height,width), dtype=np.complex64)
    for i in range(height):
        for j in range(width):
            if np.sqrt((i - height/2)**2 + (j - width/2)**2) <= r:
                filter[i][j] = transform[i][j]
    return np.fft.ifft2(np.fft.ifftshift(filter)).real

def build_ideal_highpass_filter(transform: np.ndarray, r: float) -> np.ndarray:
    height, width = transform.shape
    filter = np.zeros((height,width), dtype=np.complex64)
    for i in range(height):
        for j in range(width):
            if np.sqrt((i - height/2)**2 + (j - width/2)**2) > r:
                filter[i][j] = transform[i][j]
    return np.fft.ifft2(np.fft.ifftshift(filter)).real

def build_laplacian_highpass_filter(transform: np.ndarray) -> np.ndarray:
    height, width = transform.shape
    filter = np.zeros((height,width), dtype=np.complex64)
    for i in range(height):
        for j in range(width):
            filter[i][j] = 4 * np.pi**2 * ((i - height/2)**2 + (j - width/2)**2) * transform[i][j]
    return np.fft.ifft2(np.fft.ifftshift(filter)).real

def build_gaussian_lowpass_filter(transform: np.ndarray, s1: float, s2: float) -> np.ndarray:
    height, width = transform.shape
    filter = np.zeros((height,width), dtype=np.complex64)
    for i in range(height):
        for j in range(width):
            i_fraction = (i - height/2)**2 / (2 * s1**2)
            j_fraction = (j - width/2)**2 / (2 * s2**2)
            filter[i][j] = np.exp(-(i_fraction + j_fraction)) * transform[i][j] 
    return np.fft.ifft2(np.fft.ifftshift(filter)).real

def build_butterworth_lowpass_filter(transform: np.ndarray, d0: float, n: float) -> np.ndarray:
    height, width = transform.shape
    filter = np.zeros((height,width), dtype=np.complex64)
    for i in range(height):
        for j in range(width):
            sqrt = np.sqrt((i - height/2)**2 + (j-width/2)**2)
            filter[i][j] = 1 / (1 + (sqrt/d0)**(2*n)) * transform[i][j]
    return np.fft.ifft2(np.fft.ifftshift(filter)).real

def build_butterworth_highpass_filter(transform: np.ndarray, d0: float, n: float) -> np.ndarray:
    height, width = transform.shape
    filter = np.zeros((height,width), dtype=np.complex64)
    for i in range(height):
        for j in range(width):
            sqrt = np.sqrt((i - height/2)**2 + (j-width/2)**2)
            if sqrt > 0:
                filter[i][j] = 1 / (1 + (d0/sqrt)**(2*n)) * transform[i][j]
    return np.fft.ifft2(np.fft.ifftshift(filter)).real

def normalize_image(image: np.ndarray) -> np.ndarray: 
	return ((image - image.min()) * 255) / (image.max() - image.min())

def evaluate_rmse(expected_img: np.ndarray, filtered_img: np.ndarray) -> float:
    height, width = expected_img.shape
    sum = 0
    for i in range(height):
        for j in range(width):
           sum += (int(expected_img[i][j]) - int(filtered_img[i][j])) ** 2
    return np.sqrt(sum / (height * width))

def main():
    params = read_input_params()
    input_img = iio.imread(params['input_name'])
    transform = np.fft.fftshift(np.fft.fft2(input_img))
    filtered_img = apply_frequency_filter(transform, params)
    output_img = iio.imread(params['output_name'])
    rmse = evaluate_rmse(output_img, filtered_img)
    print(np.round(rmse, 4))
    iio.imwrite('output.png', filtered_img)

if __name__ == '__main__':
    main()
