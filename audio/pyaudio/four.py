from scipy.fftpack import fft, irfft
import matplotlib.pyplot as plt
import numpy as np

def fplot(data, duration=1):
    N = len(data)
    T = duration/N
    yf = fft(data)
    xf = np.linspace(0.0, 1.0/(2.0*T), N//2)
    amp = 2.0/N * np.abs(yf[0:N//2])
    plt.plot(xf, amp)
    plt.grid()
    plt.show()
    return xf, amp


