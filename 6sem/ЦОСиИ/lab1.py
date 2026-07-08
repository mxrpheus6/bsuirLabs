import matplotlib.pyplot as plt
import numpy as np
from scipy.io.wavfile import write

import my_fft

def draw_plot():
    # Sampling rate
    sr = 32
    # Sampling interval
    ts = 1.0 / sr
    t = np.arange(0, 1, ts)

    A = 5
    B = 2
    K = 2

    # Generate a signal
    x = A * np.sin(t) + B * np.cos(t)

    write('original_signal.wav', sr, x.astype(np.float32))

    plt.figure(figsize=(12, 6))
    plt.subplot(2, 3, 1)
    plt.plot(t, x, 'm')
    plt.xlabel('Time (t)')
    plt.ylabel('Amplitude')
    plt.title("Source signal")

    # Custom FFT
    X = my_fft.fft(x)

    # Calculate the frequency
    N = len(X)
    n = np.arange(N)
    T = N / sr
    freq = n / T

    plt.subplot(2, 3, 2)
    plt.stem(freq, np.abs(X))
    plt.xlabel('Freq (Hz)')
    plt.ylabel('FFT Amplitude')
    plt.title("My FFT")

    # Custom iFFT
    X_inv = my_fft.fft(X, inverse=True)

    write('ifft_signal.wav', sr, np.real(X_inv).astype(np.float32))

    plt.subplot(2, 3, 3)
    plt.plot(t, np.real(X_inv))
    plt.ylabel('Amplitude')
    plt.title("My iFFT")

    # Library FFT
    X_lib = np.fft.fft(x)

    plt.subplot(2, 3, 5)
    plt.stem(freq, np.abs(X_lib), 'g')
    plt.xlabel('Freq (Hz)')
    plt.ylabel('FFT Amplitude')
    plt.title("Lib FFT")

    # Library iFFT
    X_lib_inv = np.fft.ifft(X_lib)

    plt.subplot(2, 3, 6)
    plt.plot(t, np.real(X_lib_inv), 'g')
    plt.xlabel('Time (t)')
    plt.ylabel('Amplitude')
    plt.title("Lib iFFT")

    plt.tight_layout()
    plt.show()

    # Generate a signal
    x_k = (A / K) * np.sin(t) + (B / K) * np.cos(t)

    plt.figure(figsize=(12, 6))
    plt.subplot(2, 3, 1)
    plt.plot(t, x, 'm')
    plt.xlabel('Time (t)')
    plt.ylabel('Amplitude')
    plt.title("Source signal")

    plt.subplot(2, 3, 4)
    plt.plot(t, x_k, 'm')
    plt.xlabel('Time (t)')
    plt.ylabel('Amplitude')
    plt.title("Source signal (A / K) & (B / K)")

    # Custom FFT
    X_K = my_fft.fft(x_k)

    # Calculate the frequency
    N_K = len(X_K)
    n_k = np.arange(N_K)
    T_K = N_K / sr
    freq_k = n_k / T_K

    plt.subplot(2, 3, 2)
    plt.stem(freq_k, np.abs(X_K))
    plt.xlabel('Freq (Hz)')
    plt.ylabel('FFT Amplitude')
    plt.title("My FFT")

    # Custom iFFT
    X_K_inv = my_fft.fft(X_K, inverse=True)

    plt.subplot(2, 3, 3)
    plt.plot(t, np.real(X_K_inv))
    plt.ylabel('Amplitude')
    plt.title("My iFFT")

    # Library FFT
    X_K_lib = np.fft.fft(x_k)

    plt.subplot(2, 3, 5)
    plt.stem(freq_k, np.abs(X_K_lib), 'g')
    plt.xlabel('Freq (Hz)')
    plt.ylabel('FFT Amplitude')
    plt.title("Lib FFT")

    # Library iFFT
    X_K_lib_inv = np.fft.ifft(X_K_lib)

    plt.subplot(2, 3, 6)
    plt.plot(t, np.real(X_K_lib_inv), 'g')
    plt.xlabel('Time (t)')
    plt.ylabel('Amplitude')
    plt.title("Lib iFFT")

    plt.tight_layout()
    plt.show()

    plt.figure(figsize=(12, 6))

    # Generate a signal
    x_zero = A * np.sin(t) + B * np.cos(t)

    plt.subplot(2, 3, 1)
    plt.plot(t, x_zero, 'm')
    plt.xlabel('Time (t)')
    plt.ylabel('Amplitude')
    plt.title("Source signal")

    # Custom FFT
    X_zero = my_fft.fft(x_zero)

    # Zero out the second half of the spectrum
    X_zero[:len(X_zero) // 2] = 0

    # Calculate the frequency
    N_zero = len(X_zero)
    n_zero = np.arange(N_zero)
    T_zero = N_zero / sr
    freq_zero = n_zero / T_zero

    plt.subplot(2, 3, 2)
    plt.stem(freq_zero, np.abs(X_zero))
    plt.xlabel('Freq (Hz)')
    plt.ylabel('FFT Amplitude')
    plt.title("My FFT (Half Zeroed)")

    # Custom iFFT
    X_zero_inv = my_fft.fft(X_zero, inverse=True)

    plt.subplot(2, 3, 3)
    plt.plot(t, np.real(X_zero_inv))
    plt.ylabel('Amplitude')
    plt.title("My iFFT (Half Zeroed)")

    # Library FFT
    X_zero_lib = np.fft.fft(x_zero)

    # Zero out the second half of the spectrum
    X_zero_lib[:len(X_zero_lib) // 2] = 0

    plt.subplot(2, 3, 5)
    plt.stem(freq_zero, np.abs(X_zero_lib), 'g')
    plt.xlabel('Freq (Hz)')
    plt.ylabel('FFT Amplitude')
    plt.title("Lib FFT (Half Zeroed)")

    # Library iFFT
    X_zero_lib_inv = np.fft.ifft(X_zero_lib)

    plt.subplot(2, 3, 6)
    plt.plot(t, np.real(X_zero_lib_inv), 'g')
    plt.xlabel('Time (t)')
    plt.ylabel('Amplitude')
    plt.title("Lib iFFT (Half Zeroed)")

    plt.tight_layout()
    plt.show()

def main():
    draw_plot()

if __name__ == "__main__":
    main()