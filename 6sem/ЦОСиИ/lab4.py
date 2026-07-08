import numpy as np
import matplotlib.pyplot as plt
from scipy import signal as scipy_signal
import soundfile as sf

def my_convolve(signal, filter_kernel, mode='same'):
    # Инвертируем фильтр
    filter_kernel = filter_kernel[::-1]

    # Размеры сигнала и фильтра
    signal_len = len(signal)
    filter_len = len(filter_kernel)

    # Определяем размер выходного массива
    if mode == 'full':
        output_len = signal_len + filter_len - 1
    elif mode == 'same':
        output_len = signal_len
    elif mode == 'valid':
        output_len = signal_len - filter_len + 1
    else:
        raise ValueError("Неподдерживаемый режим. Используйте 'full', 'same' или 'valid'.")

    # Создаем массив для результата
    result = np.zeros(output_len)

    # Добавляем нули по краям сигнала для корректной обработки границ
    padded_signal = np.pad(signal, (filter_len // 2, filter_len // 2), mode='wrap')

    # Вычисляем свертку
    for n in range(output_len):
        # Сдвигаем фильтр относительно сигнала
        result[n] = np.sum(padded_signal[n:n + filter_len] * filter_kernel)

    return result

def blackman_window(M):
    values = np.array([0.0, M])
    M = values[1]

    if M < 1:
        return np.array([], dtype=values.dtype)
    if M == 1:
        return np.ones(1, dtype=values.dtype)

    n = np.arange(1 - M, M, 2)
    return 0.42 + 0.5 * np.cos(np.pi * n / (M - 1)) + 0.08 * np.cos(2.0 * np.pi * n / (M - 1))

def bandpass_fir_blackman(fs, f_low, f_high, numtaps=101):
    # нормализация частот
    nyq = fs / 2
    low = f_low / nyq
    high = f_high / nyq
    # получаем импульсную характеристику
    m = np.arange(numtaps) - (numtaps - 1) / 2
    h = high * np.sinc(high * m) - low * np.sinc(low * m)

    h *= blackman_window(numtaps)

    # применение весовой функции и получение коэффициентов
    center_freq = 0.5 * (low + high)
    h /= np.sum(h * np.cos(np.pi * m * center_freq))

    return h

def apply_fir_filter(signal, taps):
    """Применение КИХ-фильтра к сигналу."""
    return my_convolve(signal, taps, mode='same')

def single_pole_lpf(x, alpha):
    """Однополюсный рекурсивный НЧ-фильтр."""
    y = np.zeros_like(x)
    y[0] = x[0]
    for i in range(1, len(x)):
        y[i] = alpha * y[i - 1] + (1 - alpha) * x[i]
    return y

def four_stage_lpf(x, alpha):
    """4-каскадный однополюсный НЧ-фильтр."""
    y = x.copy()
    for _ in range(4):
        y = single_pole_lpf(y, alpha)
    return y

def plot_signal(signal, title, fs=1.0):
    """Визуализация сигнала."""
    t = np.arange(len(signal)) / fs
    plt.figure(figsize=(10, 4))
    plt.plot(t, signal)
    plt.title(title)
    plt.xlabel('Время, с')
    plt.ylabel('Амплитуда')
    plt.grid()
    plt.show()

def plot_frequency_response(taps, fs, title):
    """Визуализация АЧХ фильтра."""
    w, h = scipy_signal.freqz(taps, worN=8000, fs=fs)
    plt.figure(figsize=(10, 4))
    plt.plot(w, 20 * np.log10(np.abs(h)))
    plt.title(title)
    plt.xlabel('Частота (Гц)')
    plt.ylabel('Амплитуда (дБ)')
    plt.grid()
    plt.ylim(-100, 5)

def plot_lpf_frequency_response(alpha, fs, title):
    """Визуализация АЧХ 4-каскадного НЧ-фильтра."""
    # Частотная характеристика одного каскада
    b = [1 - alpha]  # Числитель передаточной функции
    a = [1, -alpha]  # Знаменатель передаточной функции

    # Каскадирование 4 раза
    w, h = scipy_signal.freqz(b, a, worN=8000, fs=fs)
    h_total = h ** 4  # Перемножаем передаточные функции каскадов

    # Построение графика
    plt.figure(figsize=(10, 4))
    plt.plot(w, 20 * np.log10(np.abs(h_total)))
    plt.title(title)
    plt.xlabel('Частота (Гц)')
    plt.ylabel('Амплитуда (дБ)')
    plt.grid()
    plt.ylim(-100, 5)
    plt.show()

def plot_filter_zones(fs, f_pass_low, f_pass_high, f_stop_low, f_stop_high, ripple_pass, attenuation_stop):
    """Визуализация зон фильтра."""
    plt.figure(figsize=(10, 4))
    plt.axvspan(f_pass_low, f_pass_high, color='green', alpha=0.1, label='Полоса пропускания')
    plt.axvspan(0, f_stop_low, color='red', alpha=0.1, label='Полоса подавления (низкие частоты)')
    plt.axvspan(f_stop_high, fs / 2, color='red', alpha=0.1, label='Полоса подавления (высокие частоты)')
    plt.axvspan(f_stop_low, f_pass_low, color='yellow', alpha=0.1, label='Переходная зона (низкие)')
    plt.axvspan(f_pass_high, f_stop_high, color='yellow', alpha=0.1, label='Переходная зона (высокие)')
    plt.axhline(-ripple_pass, color='green', linestyle='--', label=f'Допуск в полосе пропускания ({ripple_pass} дБ)')
    plt.axhline(-attenuation_stop, color='red', linestyle='--', label=f'Ослабление в полосе подавления -58 дБ)')
    plt.title('Характеристики фильтра')
    plt.xlabel('Частота (Гц)')
    plt.ylabel('Амплитуда (дБ)')
    plt.legend()
    plt.grid()
    plt.ylim(-100, 5)
    plt.xlim(0, fs / 2)
    plt.show()

def plot_frequency_response_with_zones(taps, fs, title, f_pass_low, f_pass_high, f_stop_low, f_stop_high, ripple_pass, attenuation_stop):
    """Визуализация АЧХ фильтра вместе с зонами фильтра."""
    # Вычисление частотной характеристики фильтра
    w, h = scipy_signal.freqz(taps, worN=8000, fs=fs)

    # Создание графика
    plt.figure(figsize=(12, 6))

    # Отображение АЧХ фильтра
    plt.plot(w, 20 * np.log10(np.abs(h)), label='АЧХ фильтра', color='blue')

    # Отображение зон фильтра
    plt.axvspan(f_pass_low, f_pass_high, color='green', alpha=0.1, label='Полоса пропускания')
    plt.axvspan(0, f_stop_low, color='red', alpha=0.1, label='Полоса подавления (низкие частоты)')
    plt.axvspan(f_stop_high, fs / 2, color='red', alpha=0.1, label='Полоса подавления (высокие частоты)')
    plt.axvspan(f_stop_low, f_pass_low, color='yellow', alpha=0.1, label='Переходная зона (низкие)')
    plt.axvspan(f_pass_high, f_stop_high, color='yellow', alpha=0.1, label='Переходная зона (высокие)')
    plt.axhline(-ripple_pass, color='green', linestyle='--', label=f'Допуск в полосе пропускания ({ripple_pass} дБ)')
    plt.axhline(-attenuation_stop, color='red', linestyle='--', label=f'Ослабление в полосе подавления -58 дБ)')

    # Настройка графика
    plt.title(title)
    plt.xlabel('Частота (Гц)')
    plt.ylabel('Амплитуда (дБ)')
    plt.grid()
    plt.ylim(-100, 5)
    plt.xlim(0, fs / 2)
    plt.legend(loc='upper right')

    # Показать график
    plt.show()

def generate_test_signal(fs, duration):
    """Генерация тестового сигнала."""
    t = np.linspace(0, duration, int(fs * duration), endpoint=False)
    f1 = 100  # Низкая частота (в полосе подавления)
    f2 = 500  # Средняя частота (в полосе пропускания)
    f3 = 1000  # Высокая частота (в полосе подавления)
    signal = (
        0.5 * np.sin(2 * np.pi * f1 * t) +
        0.8 * np.sin(2 * np.pi * f2 * t) +
        0.3 * np.sin(2 * np.pi * f3 * t) +
        0.5 * np.random.normal(size=len(t))
    )
    return t, signal

if __name__ == "__main__":
    # Параметры сигнала
    fs = 8000  # Частота дискретизации
    duration = 0.2  # Длительность сигнала

    # Генерация тестового сигнала
    t, test_signal = generate_test_signal(fs, duration)
    plot_signal(test_signal, "Исходный сигнал с шумом", fs)

    # Параметры полосового фильтра
    f_low = 400  # Нижняя частота полосы пропускания
    f_high = 600  # Верхняя частота полосы пропускания
    numtaps = 101  # Количество коэффициентов (чем больше, тем круче склоны АЧХ)

    # Создание фильтра
    taps = bandpass_fir_blackman(fs, f_low, f_high, numtaps)
    #plot_frequency_response(taps, fs, "АЧХ полосового фильтра с окном Блэкмана")

    # Параметры для визуализации зон
    ripple_pass = 0.001  # Допустимая неравномерность в полосе пропускания (дБ)
    attenuation_stop = 60  # Требуемое ослабление в полосе подавления (дБ)
    f_stop_low = 500 - 317  # Нижняя граница полосы подавления
    f_stop_high = 500 + 317 # Верхняя граница полосы подавления

    plot_frequency_response_with_zones(
        taps, fs, "АЧХ полосового фильтра с окном Блэкмана и зоны фильтра",
        f_low, f_high, f_stop_low, f_stop_high, ripple_pass, attenuation_stop
    )
    #plot_filter_zones(fs, f_low, f_high, f_stop_low, f_stop_high, ripple_pass, attenuation_stop)

    # Применение фильтра
    filtered_bp = apply_fir_filter(test_signal, taps)
    plot_signal(filtered_bp, "Сигнал после полосового фильтра с окном Блэкмана", fs)

    # 4-каскадный НЧ-фильтр
    cutoff_freq = 300  # Частота среза
    alpha = np.exp(-2 * np.pi * cutoff_freq / fs)  # Параметр фильтра
    plot_lpf_frequency_response(alpha, fs, "АЧХ 4-каскадного НЧ-фильтра")
    filtered_lp = four_stage_lpf(test_signal, alpha)
    plot_signal(filtered_lp, "Сигнал после 4-каскадного НЧ-фильтра", fs)

    # Визуализация всех сигналов
    plt.figure(figsize=(12, 6))
    plt.plot(t, test_signal, label='Исходный сигнал', alpha=0.7)
    plt.plot(t, filtered_bp, label='После полосового фильтра с окном Блэкмана', linewidth=2)
    plt.plot(t, filtered_lp, label='После после 4-каскадного НЧ-фильтра', linewidth=2)
    plt.title('Сравнение фильтров')
    plt.xlabel('Время, с')
    plt.ylabel('Амплитуда')
    plt.legend()
    plt.grid()
    plt.show()

    try:
        print('Чтение аудиофайла')
        # Чтение аудиофайла
        audio, audio_fs = sf.read('audio.wav')
        if len(audio.shape) > 1:
            audio = audio[:, 0]  # Берем первый канал если стерео

        # Нормализация
        audio = audio / np.max(np.abs(audio))

        print('Блэкман...')
        taps_audio = bandpass_fir_blackman(audio_fs, 80, 300, 401)
        filtered_audio_bp = apply_fir_filter(audio, taps_audio)

        print('НЧ...')
        alpha_audio = np.exp(-2 * np.pi * 300 / audio_fs)
        filtered_audio_lp = four_stage_lpf(audio, alpha_audio)

        # Сохранение результатов
        sf.write('filtered_bp.wav', filtered_audio_bp, audio_fs)
        sf.write('filtered_lp.wav', filtered_audio_lp, audio_fs)

        print("Аудиофильтрация завершена. Результаты сохранены.")
    except Exception as e:
        print(f"Не удалось обработать аудиофайл: {e}")