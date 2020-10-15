import numpy as np
from matplotlib import pyplot as plt

zeit, counts = np.genfromtxt("Data/average_signal.txt",skip_header=2, unpack = True)
plt.plot(zeit, counts, marker = 'o',  color = 'magenta', linestyle = 'None', label="Messwerte")
plt.plot(zeit[6], counts[6], marker = '*',  color = 'dodgerblue',markersize=12, linestyle = 'None', label="Maximum")
plt.vlines(x=48, ymin=-1, ymax=95.607734, color = 'dodgerblue', linestyle = '--')
plt.hlines(y=95.607734, xmin=-1, xmax=48, color = 'dodgerblue', linestyle = '--')
plt.xlim(-1, 251)
plt.ylim(-1, 100)
plt.legend()
plt.grid()
plt.xlabel("Zeit in ns")
plt.ylabel("ADC")
plt.savefig("plots/delay_messung.pdf")
