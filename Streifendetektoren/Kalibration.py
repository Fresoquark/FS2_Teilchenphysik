import numpy as np
from matplotlib import pyplot as plt
from scipy import constants
from scipy.constants import elementary_charge

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

plt.clf()

#Kalibrationsmessung
energie1, ADC1 = np.genfromtxt("Data/Calib/calib_10.txt",skip_header=2, unpack = True)
energie2, ADC2 = np.genfromtxt("Data/Calib/calib_20.txt",skip_header=2, unpack = True)
energie3, ADC3 = np.genfromtxt("Data/Calib/calib_30.txt",skip_header=2, unpack = True)
energie4, ADC4 = np.genfromtxt("Data/Calib/calib_40.txt",skip_header=2, unpack = True)
energie4_0V, ADC4_0V = np.genfromtxt("Data/Calib/calib_40_0V.txt",skip_header=2, unpack = True)



energie1 = energie1 /1e6*3.6
energie2 = energie2 /1e6*3.6
energie3 = energie3 /1e6*3.6
energie4 = energie4 /1e6*3.6
energie4_0V = energie4_0V /1e6*3.6



plt.plot(energie1, ADC1, marker = '.',  color = 'magenta', linestyle = 'None', label="Kanal 10")
plt.legend()
plt.grid()
plt.xlabel("Energie in MeV")
plt.ylabel("ADC")
plt.savefig("plots/calib_channel10.pdf")
plt.clf()

plt.plot(energie2, ADC2, marker = '.',  color = 'magenta', linestyle = 'None', label="Kanal 20")
plt.legend()
plt.grid()
plt.xlabel("Energie in MeV")
plt.ylabel("ADC")
plt.savefig("plots/calib_channel20.pdf")
plt.clf()

plt.plot(energie3, ADC3, marker = '.',  color = 'magenta', linestyle = 'None', label="Kanal 30")
plt.legend()
plt.grid()
plt.xlabel("Energie in MeV")
plt.ylabel("ADC")
plt.savefig("plots/calib_channel30.pdf")
plt.clf()

plt.plot(energie4, ADC4, marker = '.',  color = 'magenta', linestyle = 'None', label="Kanal 40")
plt.legend()
plt.grid()
plt.xlabel("Energie in MeV")
plt.ylabel("ADC")
plt.savefig("plots/calib_channel40.pdf")
plt.clf()

plt.plot(energie4_0V, ADC4_0V, marker = '.',  color = 'magenta', linestyle = 'None', label="Kanal 40 für 0V")
plt.legend()
plt.grid()
plt.xlabel("Energie in MeV")
plt.ylabel("ADC")
plt.savefig("plots/calib_channel40_0V.pdf")
plt.clf()