import numpy as np
import matplotlib.pyplot as plt
from scipy.io.wavfile import write
from scipy.signal import convolve

import my_fft

sr = 32
ts = 1.0 / sr
t = np.arange(0, 2 * np.pi, ts)

signal1 = 5 * np.sin(t)
signal2 = 2 * np.cos(t)

def convolution(x, y):
    N = len(x)
    M = len(y)
    result = np.zeros(N + M - 1)
    for n in range(N + M - 1):
        for m in range(max(0, n - M + 1), min(n + 1, N)):
            result[n] += x[m] * y[n - m]
    return result

def correlation(x, y):
    N = len(x)
    M = len(y)
    result = np.zeros(N + M - 1)
    for n in range(N + M - 1):
        for m in range(max(0, n - M + 1), min(n + 1, N)):
            result[n] += x[m] * y[m - n + M - 1]
    return result

def fft_convolution(x, y):
    # Дополняем массивы нулями до длины x + y - 1
    n = len(x) + len(y) - 1
    x_padded = np.pad(x, (0, n - len(x)), mode='constant')
    y_padded = np.pad(y, (0, n - len(y)), mode='constant')

    # Вычисляем FFT для обоих массивов
    X = my_fft.fft(x_padded)
    Y = my_fft.fft(y_padded)

    # Поэлементное умножение в частотной области
    Z = X * Y

    # Обратное FFT для получения свертки
    z = my_fft.fft(Z, inverse=True)

    # Возвращаем только действительную часть (так как входные данные действительные)
    return np.real(z)

def fft_correlation(x, y):
    n = len(x) + len(y) - 1
    x_padded = np.pad(x, (0, n - len(x)), mode='constant')
    y_padded = np.pad(y, (0, n - len(y)), mode='constant')

    # Выполняем быстрое преобразование Фурье для обоих сигналов
    X = my_fft.fft(x_padded)
    Y = my_fft.fft(y_padded)

    # Умножаем спектр X на комплексно сопряженный спектр Y
    result_fft = X * np.conj(Y)

    # Выполняем обратное преобразование Фурье для получения корреляции
    result = my_fft.fft(result_fft, inverse=True)

    # Возвращаем только действительную часть результата
    result = np.real(result)
    result = np.fft.fftshift(result)

    return result

conv_lib = convolve(signal1, signal2, mode='full')  # Свёртка (SciPy)
corr_lib = np.correlate(signal1, signal2, mode='full')  # Корреляция (NumPy)

conv_result = convolution(signal1, signal2)
corr_result = correlation(signal1, signal2)

fft_conv_result = fft_convolution(signal1, signal2)
fft_corr_result = fft_correlation(signal1, signal2)

write('conv_own.wav', sr, conv_result.astype(np.float32))
write('conv_fft.wav', sr, fft_conv_result.astype(np.float32))

def plot_comparison(t, signal1, signal2, conv_result, corr_result, conv_lib, corr_lib, fft_conv_result, fft_corr_result):
    plt.figure(figsize=(15, 12))

    # Первая строка: исходные сигналы
    plt.subplot(3, 3, 1)
    plt.plot(t, signal1, label='5*sin(x)', color='purple')
    plt.plot(t, signal2, label='2*cos(x)', color='yellow')
    plt.title('Исходные сигналы')
    plt.xlabel('Время (сек)')
    plt.ylabel('Амплитуда')
    plt.legend()

    # Вторая строка: свертки
    plt.subplot(3, 3, 4)
    plt.plot(conv_result)
    plt.title('Свёртка (наша)')
    plt.xlabel('Отсчеты')
    plt.ylabel('Амплитуда')

    plt.subplot(3, 3, 5)
    plt.plot(conv_lib, linestyle='dashed', color='red')
    plt.title('Свёртка (библиотечная)')
    plt.xlabel('Отсчеты')
    plt.ylabel('Амплитуда')

    plt.subplot(3, 3, 6)
    plt.plot(fft_conv_result, color='green')
    plt.title('Свертка через FFT')
    plt.xlabel('Отсчеты')
    plt.ylabel('Амплитуда')

    # Третья строка: корреляции
    plt.subplot(3, 3, 7)
    plt.plot(corr_result)
    plt.title('Корреляция (наша)')
    plt.xlabel('Отсчеты')
    plt.ylabel('Амплитуда')

    plt.subplot(3, 3, 8)
    plt.plot(corr_lib, linestyle='dashed', color='red')
    plt.title('Корреляция (библиотечная)')
    plt.xlabel('Отсчеты')
    plt.ylabel('Амплитуда')

    plt.subplot(3, 3, 9)
    plt.plot(fft_corr_result, color='green')
    plt.title('Корреляция через FFT')
    plt.xlabel('Отсчеты')
    plt.ylabel('Амплитуда')

    plt.tight_layout()
    plt.show()

plot_comparison(t, signal1, signal2, conv_result, corr_result, conv_lib, corr_lib, fft_conv_result, fft_corr_result)

conv_self = convolution(signal1, signal1)
corr_self = correlation(signal1, signal1)

conv_self_lib = convolve(signal1, signal1, mode='full')
corr_self_lib = np.correlate(signal1, signal1, mode='full')

def plot_self_comparison(t, signal1, conv_self, corr_self, conv_self_lib, corr_self_lib):
    plt.figure(figsize=(15, 10))

    # Исходный сигнал
    plt.subplot(3, 2, 1)
    plt.plot(t, signal1, label='5*sin(x)', color='blue')
    plt.title('Исходный сигнал (signal1)')
    plt.xlabel('Время (сек)')
    plt.ylabel('Амплитуда')
    plt.legend()

    # Свертка сигнала с самим собой
    plt.subplot(3, 2, 3)
    plt.plot(conv_self, color='orange')
    plt.title('Автосвёртка (наша)')
    plt.xlabel('Отсчеты')
    plt.ylabel('Амплитуда')

    plt.subplot(3, 2, 4)
    plt.plot(conv_self_lib, linestyle='dashed', color='red')
    plt.title('Автосвёртка (библиотечная)')
    plt.xlabel('Отсчеты')
    plt.ylabel('Амплитуда')

    # Корреляция сигнала с самим собой
    plt.subplot(3, 2, 5)
    plt.plot(corr_self, color='orange')
    plt.title('Автокорреляция (наша)')
    plt.xlabel('Отсчеты')
    plt.ylabel('Амплитуда')

    plt.subplot(3, 2, 6)
    plt.plot(corr_self_lib, linestyle='dashed', color='red')
    plt.title('Автокорреляция (библиотечная)')
    plt.xlabel('Отсчеты')
    plt.ylabel('Амплитуда')

    plt.tight_layout()
    plt.show()

plot_self_comparison(t, signal1, conv_self, corr_self, conv_self_lib, corr_self_lib)