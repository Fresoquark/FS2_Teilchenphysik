import numpy as np
from matplotlib import pyplot as plt
from numpy.random import normal

strips = np.arange(0, 127)

data = np.genfromtxt("Data/Pedestal.txt", delimiter = ";")

means = []

#Pedestals
for i in strips:
    means.append(np.mean(data[i]))

plt.plot(strips, means, marker = 'p',  color = 'magenta', linestyle = 'None' , label="Pedestals")
plt.legend()
plt.grid()
plt.xlabel("Channel")
plt.ylabel("ADC")
plt.savefig("plots/pedestals.pdf")
plt.clf()

common = []

#Common Shift
for i in range(0, 999):
    dshift = 0
    for j in strips:
        dshift += data[j][i] - means[j]
    dshift *= 1/128
    common.append(dshift)


mean_hist = np.mean(common)
variance_hist = np.var(common)
sigma_hist = np.sqrt(variance_hist)

mean_hist_theorie = 0 
gaussian_numbers = normal(mean_hist_theorie, sigma_hist, 99999999)


noise = []
#Noise
for i in strips:
    N = len(data[i])
    noisetemp = 0
    for j in range(0, 999):
        noisetemp += (data[i][j] - means[i] - common[j])**2
    noise.append(np.sqrt(1/(N - 1) * noisetemp))

plt.plot(strips, noise, marker = 'o',  color = 'magenta', linestyle = 'None' , label="Noise")
plt.legend()
plt.grid()
plt.xlabel("Channel")
plt.ylabel("ADC")
plt.savefig("plots/noise.pdf")
plt. clf()

plt.hist(common, bins=15, range=[-15, 15], label="Shift", weights=np.ones(len(common)) / len(common), color = 'magenta', alpha=0.6)
plt.hist(gaussian_numbers, bins=15, range=[-15, 15], label="Theorie-Gauß", weights= np.ones(len(gaussian_numbers))/ len(gaussian_numbers), color = 'dodgerblue', alpha = 0.4)
plt.legend()
plt.grid()
plt.xlabel("Common Mode Shift")
plt.ylabel("ADC")
plt.savefig("plots/cshift.pdf")
plt. clf()





















#
