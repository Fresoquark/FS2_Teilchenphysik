import numpy as np
from matplotlib import pyplot as plt

strips = np.arange(0, 127)

data = np.genfromtxt("Data/Pedestal.txt", delimiter = ";")

means = []

#Pedestals
for i in strips:
    means.append(np.mean(data[i]))

plt.plot(strips, means, 'bo', label="Pedestals")
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

noise = []
#Noise
for i in strips:
    N = len(data[i])
    noisetemp = 0
    for j in range(0, 999):
        noisetemp += (data[i][j] - means[i] - common[j])**2
    noise.append(np.sqrt(1/(N - 1) * noisetemp))

plt.plot(strips, noise, 'bo', label="Noise")
plt.legend()
plt.grid()
plt.xlabel("Channel")
plt.ylabel("ADC")
plt.savefig("plots/noise.pdf")
plt. clf()

plt.hist(common, bins=15, range=[-15, 15], label="Shift", weights=np.ones(len(common)) / len(common))
plt.legend()
plt.grid()
plt.xlabel("Channel")
plt.ylabel("ADC")
plt.savefig("plots/cshift.pdf")
plt. clf()





















#
