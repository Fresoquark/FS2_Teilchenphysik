import numpy as np
from matplotlib import pyplot as plt
from scipy import constants
from scipy import optimize
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



energie1 = (energie1 /1e6)*3.6
energie2 = (energie2 /1e6)*3.6
energie3 = (energie3 /1e6)*3.6
energie4 = (energie4 /1e6)*3.6
energie4_0V = (energie4_0V /1e6)*3.6



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

plt.plot(energie4_0V, ADC4_0V, marker = '.',  color = 'magenta', linestyle = 'None', label="Kanal 40 für 0V")
plt.plot(energie4, ADC4, marker = '.',  color = 'dodgerblue', linestyle = 'None', label="Kanal 40 $U > U_{dep}$")
plt.legend()
plt.grid()
plt.xlabel("Energie in MeV")
plt.ylabel("ADC")
plt.savefig("plots/calib_channel40_comparison.pdf")
plt.clf()

mean_ADC = []
mean_pulses = []

for i in range(len(ADC1)):
    ADC_summe = ADC1[i] + ADC2[i] + ADC3[i] +ADC4[i]
    mean_A = ADC_summe / 4 
    mean_ADC.append(mean_A)

for i in range(len(energie1)):
    e_summe = energie1[i] + energie2[i] + energie3[i] +energie4[i]
    mean_e = e_summe / 4 
    mean_pulses.append(mean_e)

mean_fit_ADC = mean_ADC[:140]
mean_fit_pulses = mean_pulses[:140]

print("#####################################################################################")
print("Letzter Wert der Funktion: ", mean_fit_ADC[139])
print("#####################################################################################")


def poly4(mean_fit_ADC, a , b, c, d, e):
    return a + (np.array(mean_fit_ADC) * b) + ((np.array(mean_fit_ADC)**2) * c) + ((np.array(mean_fit_ADC)**3) * d) + ((np.array(mean_fit_ADC)**4) * e)

params, params_covariance = optimize.curve_fit(poly4, mean_fit_ADC, mean_fit_pulses)

print("#####################################################################################")
print("Die Params haben die Dimension MeV")
print("Das Polynom der Form: a + bx + cx**2 + dx**3 + ex**4 besitzt die folgenden Parameter:")
print("Parameter a: ", params[0], "+-", params_covariance[0][0])
print("Parameter b: ", params[1], "+-", params_covariance[1][1])
print("Parameter c: ", params[2], "+-", params_covariance[2][2])
print("Parameter d: ", params[3], "+-", params_covariance[3][3])
print("Parameter e: ", params[4], "+-", params_covariance[4][4])
print("#####################################################################################")

plt.plot(mean_ADC, mean_pulses , marker = '.',  color = 'magenta', linestyle = 'None', label="Mittelwert der Elektronenpulse", alpha = 0.4)
plt.plot(mean_fit_ADC, poly4(mean_fit_ADC, params[0], params[1], params[2], params[3], params[4]), label='Polynom 4. Grades', color = "dodgerblue", linewidth = 2.5)
plt.legend()
plt.grid()
plt.ylabel("Energie in MeV")
plt.xlabel("ADC")
plt.savefig("plots/calib_mean.pdf")
