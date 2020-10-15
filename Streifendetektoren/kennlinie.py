import numpy as np
from matplotlib import pyplot as plt

spannung, strom = np.genfromtxt("Data/Kennlinie_Strom_Spannung.txt", unpack = True)

plt.plot(spannung, strom, marker = 'o',  color = 'magenta', linestyle = 'None', label="Messwerte")
plt.legend()
plt.grid()
plt.xlabel("Spannung in V")
plt.ylabel("Strom in A")
plt.savefig("plots/kennlinie.pdf")
