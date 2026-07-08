import numpy as np
import matplotlib.pyplot as plt

# Функция для дополнения сигнала до четной длины
def pad_to_even(signal):
    if len(signal) % 2 != 0:
        # Дополняем сигнал нулем, чтобы длина стала четной
        signal = np.append(signal, 0)
    return signal

# Лифтинг-схема: прямое преобразование
def lifting_dwt(signal):
    # Убедимся, что длина сигнала четная
    signal = pad_to_even(signal)

    # Разделение сигнала на четные и нечетные элементы
    even = signal[::2]
    odd = signal[1::2]

    # Этап предсказания (predict): вычисляем детализирующие коэффициенты
    detail = odd - even

    # Этап обновления (update): вычисляем аппроксимирующие коэффициенты
    approx = even + detail / 2

    return approx, detail

# Лифтинг-схема: обратное преобразование
def lifting_idwt(approx, detail):
    # Проверяем длины массивов и обрезаем более длинный массив до размера короткого
    min_length = min(len(approx), len(detail))
    approx = approx[:min_length]
    detail = detail[:min_length]

    # Этап восстановления обновления (inverse update)
    even = approx - detail / 2

    # Этап восстановления предсказания (inverse predict)
    odd = detail + even

    # Сборка сигнала из четных и нечетных элементов
    reconstructed = np.zeros(len(approx) + len(detail))
    reconstructed[::2] = even
    reconstructed[1::2] = odd

    return reconstructed

# Применение операций к детализирующим коэффициентам
def apply_operations(details, operations):
    corrected_details = details.copy()

    for level, (operation, param) in operations.items():
        if operation == "none":
            pass
        elif operation == "zero":
            corrected_details[level] = np.zeros_like(details[level])
        elif operation == "scale":
            corrected_details[level] = details[level] * param
        elif operation == "add":
            corrected_details[level] = details[level] + param
        else:
            raise ValueError(f"Неизвестная операция: {operation}")

    return corrected_details

# Генерация сигнала
sr = 32
ts = 1.0 / sr
t = np.arange(0, 2 * np.pi, ts)

signal = 5 * np.sin(t) + 2 * np.cos(t)

# Визуализация исходного сигнала
plt.figure(figsize=(12, 6))
plt.plot(t, signal, label="Исходный сигнал")
plt.title("Исходный сигнал")
plt.xlabel("Время (с)")
plt.ylabel("Амплитуда")
plt.legend()
plt.grid()
plt.show()

# Генерация шума
np.random.seed(42)
noise = 2 * np.random.rand(len(signal)) - 1  # [-1, 1]

# Зашумленный сигнал
noisy_signal = signal + noise

# Визуализация зашумленного сигнала
plt.figure(figsize=(12, 6))
plt.plot(t, noisy_signal, label="Зашумленный сигнал", color="orange")
plt.plot(t, signal, label="Исходный сигнал", linestyle="--", alpha=0.7)
plt.title("Зашумленный сигнал")
plt.xlabel("Время (с)")
plt.ylabel("Амплитуда")
plt.legend()
plt.grid()
plt.show()

# Разложение на L уровней с использованием лифтинг-схемы
L = 4
coeffs = [noisy_signal]  # Список для хранения коэффициентов
approximations = []
details = []

for level in range(L):
    approx, detail = lifting_dwt(coeffs[-1])
    approximations.append(approx)
    details.append(detail)
    coeffs.append(approx)

operations_good = {
    0: ("scale", 0.2),
    1: ("scale", 0.5),
    2: ("none", None),
    3: ("none", None),
}

operations_var = {
    1: ("zero", None),
    2: ("scale", 0.5),
}

corrected_details = apply_operations(details, operations_var)

# Визуализация аппроксимаций и детализирующих коэффициентов
plt.figure(figsize=(12, 8))
for i in range(L):
    plt.subplot(L, 2, 2 * i + 1)
    plt.plot(approximations[i], label=f"Аппроксимация (уровень {i+1})")
    plt.legend()
    plt.grid()

    plt.subplot(L, 2, 2 * i + 2)
    plt.plot(details[i], label=f"Детализация (уровень {i+1})", color="green")
    plt.legend()
    plt.grid()

plt.tight_layout()
plt.show()

plt.figure(figsize=(12, 8))
for i in range(L):
    plt.subplot(L, 1, 1 * i + 1)
    plt.plot(corrected_details[i], label=f"Скорректированная детализация (уровень {i+1})", color="green")
    plt.legend()
    plt.grid()

plt.tight_layout()
plt.show()

# Восстановление сигнала
reconstructed_signal = approximations[-1]
for i in reversed(range(L)):
    reconstructed_signal = lifting_idwt(reconstructed_signal, details[i])

# Визуализация восстановленного сигнала
plt.figure(figsize=(12, 6))
plt.plot(t, noisy_signal, label="Зашумленный сигнал", color="orange")
plt.plot(t[:len(reconstructed_signal)], reconstructed_signal, label="Восстановленный сигнал", linestyle="--", color="green", alpha=0.7)
plt.title("Восстановленный сигнал")
plt.xlabel("Время (с)")
plt.ylabel("Амплитуда")
plt.legend()
plt.grid()
plt.show()

# Восстановление скорректированного сигнала
corrected_signal = approximations[-1]
for i in reversed(range(L)):
    corrected_signal = lifting_idwt(corrected_signal, corrected_details[i])

# Визуализация скорректированного сигнала
plt.figure(figsize=(12, 6))
plt.title("Скорректированный сигнал")
plt.xlabel("Время (с)")
plt.ylabel("Амплитуда")
plt.grid()

plt.plot(t[:len(signal)], signal, label="Исходный сигнал", alpha=0.7)
plt.plot(t[:len(corrected_signal)], corrected_signal, label="Скорректированный сигнал", linestyle="--", color="green")
plt.legend()
plt.show()