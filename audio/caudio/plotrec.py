import matplotlib.pyplot as plt
import numpy as np

def load():
    global rec, spkr
    rec = np.loadtxt("dat.csv", delimiter=',')
    spkr = np.loadtxt("speaker.csv", delimiter=',')
    siz = min(rec.shape[0], spkr.shape[0])
    print(siz)
    return siz

def plot(showlen):
    x = np.arange(showlen)
    plt.plot(x, rec[:showlen], x, spkr[:showlen])
    plt.show()

if __name__ == '__main__':
    plot(load())
