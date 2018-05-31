import matplotlib.pyplot as plt
import numpy as np

dat = np.loadtxt("data.csv", delimiter=', ')
x = np.arange(dat.shape[0])
play = dat[:,2]
rec = dat[:,3]

plt.plot(x, play, x, rec)
plt.grid()
plt.show()
