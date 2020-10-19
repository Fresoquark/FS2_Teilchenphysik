import numpy as np
from matplotlib import pyplot as plt
from uncertainties import ufloat
from uncertainties.unumpy import (nominal_values as noms, std_devs as stds)
from scipy import optimize
import uncertainties.unumpy as unp


def gaus(x, mu, sigma, a):
    return a*np.e**(-(x-mu)**2/(2*sigma**2))

zeit, counts = np.genfromtxt("Data/laser_delay.txt", unpack = True, skip_header = 2)

plt.plot(zeit, counts, marker = 'o',  color = 'magenta', linestyle = 'None', label="Messwerte")
plt.plot(110, 190, marker = 'x', color = 'cyan', linestyle = 'None', label='Maximum')
plt.vlines(110, 0, 200, color = 'cyan', linestyle = 'dashed')
#Maximum bei 110ns
plt.legend()
plt.grid()
plt.xlabel("t in ns")
plt.ylabel("ADC")
plt.savefig("plots/lazordelay.pdf")
plt.clf()

data = np.genfromtxt("Data/Laserscan.txt")

print(data)
print(data[0][68])

strips = np.arange(0, 128)
position = np.arange(0, 35, 1)
reduposition = np.arange(0, 13, 1)
plotposition = np.arange(0, 350, 1)
plotredu = np.arange(0, 130, 1)
reduposition_2 = np.arange(12, 26, 1)
plotredu_2 = np.arange(120, 260, 1)

for i in position:
    plt.plot(strips, data[i])

plt.xlim(65,72.5)
plt.xlabel("Channel")
plt.ylabel("ADC")
plt.savefig("plots/lazorchannel.pdf")
plt. clf()

maxarr = []

#Do for alle channel
for i in range(68, 71, 1):
    #Temparray for maximum
    maximum = []
    for posi in range(0, 35, 1):
        maximum.append(data[posi][i])
    #Find index for maximum => Laserpos
    maxarr.append(np.argmax(maximum))
    #print("------------------------")

#Distance between the strips as the mean of the differences between the maxima
print("Distance between strips: ", np.mean([maxarr[0]-maxarr[1], maxarr[1]-maxarr[2]]) * 10, "micrometres")

#Channel 69
print("Stuff for Channel 69:")

newposi = []
for i in position:
    newposi.append(data[i][69])

newposi2 = []
for i in reduposition:
    newposi2.append(data[i][69])

newposi3 = []
for i in reduposition_2:
    newposi3.append(data[i][69])

params1, covariance_matrix = optimize.curve_fit(gaus, reduposition*10, newposi2)
errors = np.sqrt(np.diag(covariance_matrix))
param0 = ufloat(params1[0], errors[0])
print('mu', param0)
param1 = ufloat(params1[1], errors[1])
print('sigma', param1)


params1_2, covariance_matrix_2 = optimize.curve_fit(gaus, reduposition_2*10, newposi3, p0=[180, 20, 1])
errors_2 = np.sqrt(np.diag(covariance_matrix_2))
param0_2 = ufloat(params1_2[0], errors_2[0])
print('mu', param0_2)
param1_2 = ufloat(params1_2[1], errors_2[1])
print('sigma', param1_2)


plt.plot(position*10, newposi, marker = 'o',  color = 'black', linestyle = 'None', label="Messwerte")
plt.plot(plotredu, gaus(plotredu, *params1),  color = 'orange', linestyle = '--', label="Gauss-Fit 1")
plt.plot(plotredu_2, gaus(plotredu_2, *params1_2),  color = 'blue', linestyle = '--', label="Gauss-Fit 2")
#plt.vlines(10, 0, 170, color = 'orange', linestyle = 'dashed')
#plt.vlines(110, 0, 170, color = 'orange', linestyle = 'dashed')
#plt.vlines(65, 0, 170, color = 'red', linestyle = 'dashed')
plt.legend()
plt.grid()
plt.xlabel("Position in micrometre")
plt.ylabel("ADC")
plt.savefig("plots/lazorausdehnung_69.pdf")
plt.clf()

plt.plot(reduposition*10, newposi2, marker = 'o',  color = 'black', linestyle = 'None', label="Messwerte")
plt.plot(plotredu, gaus(plotredu, *params1),  color = 'orange', linestyle = '--', label="Gauss-Fit 1")
plt.legend()
plt.grid()
plt.xlabel("Position in micrometre")
plt.ylabel("ADC")
plt.savefig("plots/lazorausdehnung_69_1.pdf")
plt.clf()

plt.plot(reduposition_2*10, newposi3, marker = 'o',  color = 'black', linestyle = 'None', label="Messwerte")
plt.plot(plotredu_2, gaus(plotredu_2, *params1_2),  color = 'blue', linestyle = '--', label="Gauss-Fit 2")
plt.legend()
plt.grid()
plt.xlabel("Position in micrometre")
plt.ylabel("ADC")
plt.savefig("plots/lazorausdehnung_69_2.pdf")
plt.clf()

print("Stuff for Channel 68:")
reduposition_2 = np.arange(15, 28, 1)
plotredu_2 = np.arange(150, 280, 1)

newposi = []
for i in position:
    newposi.append(data[i][68])

newposi2 = []
for i in reduposition:
    newposi2.append(data[i][68])

newposi3 = []
for i in reduposition_2:
    newposi3.append(data[i][68])

params1_2, covariance_matrix_2 = optimize.curve_fit(gaus, reduposition_2*10, newposi3, p0=[180, 20, 1])
errors_2 = np.sqrt(np.diag(covariance_matrix_2))
param0_2 = ufloat(params1_2[0], errors_2[0])
print('mu', param0_2)
param1_3 = ufloat(params1_2[1], errors_2[1])
print('sigma', param1_3)

plt.plot(position*10, newposi, marker = 'o',  color = 'black', linestyle = 'None', label="Messwerte")
plt.plot(plotredu_2, gaus(plotredu_2, *params1_2),  color = 'orange', linestyle = '--', label="Gauss-Fit 1")
#plt.vlines(10, 0, 170, color = 'orange', linestyle = 'dashed')
#plt.vlines(110, 0, 170, color = 'orange', linestyle = 'dashed')
#plt.vlines(65, 0, 170, color = 'red', linestyle = 'dashed')
plt.legend()
plt.grid()
plt.xlabel("Position in micrometre")
plt.ylabel("ADC")
plt.savefig("plots/lazorausdehnung_68.pdf")
plt.clf()

plt.plot(reduposition*10, newposi2, marker = 'o',  color = 'black', linestyle = 'None', label="Messwerte")
plt.plot(plotredu, gaus(plotredu, *params1),  color = 'orange', linestyle = '--', label="Gauss-Fit 1")
plt.legend()
plt.grid()
plt.xlabel("Position in micrometre")
plt.ylabel("ADC")
plt.savefig("plots/lazorausdehnung_68_1.pdf")
plt.clf()

print("Stuff for Channel 70:")
print("Kein Fit moeglich")
newposi = []
for i in position:
    newposi.append(data[i][70])


plt.plot(position*10, newposi, marker = 'o',  color = 'black', linestyle = 'None', label="Messwerte")
#plt.plot(plotredu_2, gaus(plotredu_2, *params1_2),  color = 'orange', linestyle = '--', label="Gauss-Fit 1")
#plt.vlines(10, 0, 170, color = 'orange', linestyle = 'dashed')
#plt.vlines(110, 0, 170, color = 'orange', linestyle = 'dashed')
#plt.vlines(65, 0, 170, color = 'red', linestyle = 'dashed')
plt.legend()
plt.grid()
plt.xlabel("Position in micrometre")
plt.ylabel("ADC")
plt.savefig("plots/lazorausdehnung_70.pdf")
plt.clf()

#Durchschnittsbreite

mean_width = 1/3 * (param1 + unp.sqrt((param1_2)**2) + param1_3)
print("Durchschnittsbreite: ", mean_width)
