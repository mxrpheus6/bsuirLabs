import numpy as np
import cmath

def fft_tukey(x):
    N = len(x)
    if N <= 1:
        return x

    even = fft(x[0::2])
    odd = fft(x[1::2])

    T = [cmath.exp(-2j * cmath.pi * k / N) * odd[k] for k in range(N // 2)]
    return [even[k] + T[k] for k in range(N // 2)] + \
           [even[k] - T[k] for k in range(N // 2)]

def ifft(X):
    N = len(X)
    x = fft([x.conjugate() for x in X])
    return [x[k].conjugate() / N for k in range(N)]

def fft(vec, inverse = False):
    vec_length = len(vec)
    padding = 2 ** ((vec_length * 2).bit_length())
    sign = (-1 if inverse else 1)
    coef_arr = 1j * np.pi * (np.arange(vec_length) ** 2) / vec_length
    twd_f, twd_b = np.exp(-sign * coef_arr), np.exp(sign * coef_arr)
    x_pad, y_pad = np.zeros(padding, dtype=np.complex128), np.zeros(padding, dtype=np.complex128)
    x_pad[: vec_length] = vec * twd_b
    y_pad[: vec_length] = twd_f
    y_pad[padding - vec_length + 1:] = twd_f[: 0: -1]
    result = conv(x_pad, y_pad)[: vec_length] * twd_b
    if inverse:
        return result/vec_length
    return result


def conv(x_vec, y_vec):
    fft_x = radix2(x_vec)
    fft_y = radix2(y_vec)
    fft_x *= fft_y
    fft_x = radix2(fft_x, inverse=True)
    return fft_x

def butterfly(vec_even, vec_odd, twiddles):
    vec_length = len(vec_even) * 2
    result = np.zeros(vec_length, dtype=np.complex128)
    for k in range(vec_length // 2):
        result[k] = vec_even[k] + vec_odd[k] * twiddles[k]
        result[k + vec_length // 2] = vec_even[k] - vec_odd[k] * twiddles[k]
    return result


def radix2(vec, inverse = False):
    vec_length = len(vec)
    vec = bit_reversal(vec)
    stages = vec_length.bit_length() - 1
    for stage in range(1, stages + 1):
        size = 2 ** stage
        for i in range(0, vec_length, size):
            half_size = size // 2
            l_vec = vec[i: i + half_size]
            r_vec = vec[i + half_size: i + size]
            twd_fac = twiddle(size, size // 2, inverse)
            result = butterfly(l_vec, r_vec, twd_fac)
            vec[i: i + size] = result
    if inverse:
        return vec/vec_length
    return vec

def reverse_bits(val, width):
    result = 0
    for _ in range(width):
        result = (result << 1) | (val & 1)
        val >>= 1
    return result


def bit_reversal(vec):
    vec_length = len(vec)
    levels = vec_length.bit_length() - 1
    result = np.zeros(vec_length, dtype=np.complex128)
    for i in range(vec_length):
        result[i] = vec[reverse_bits(i, levels)]
    return result


def twiddle(size, until, inverse):
    coef = (-2 if inverse else 2) * 1j * np.pi
    return [np.exp(coef * k / size) for k in range(until)]