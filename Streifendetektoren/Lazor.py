import numpy as np
from matplotlib import pyplot as plt

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

strips = np.arange(0, 128)
position = np.arange(0, 34, 1)

for i in position:
    plt.plot(strips, data[i])

plt.xlim(65,72.5)
plt.xlabel("Channel")
plt.ylabel("ADC")
plt.savefig("plots/lazorchannel.pdf")
plt. clf()

maxarr = []

#Do for alle channel
for i in range(67, 70, 1):
    #Tem parray for maximum
    maximum = []
    for posi in range(0, 34, 1):
        maximum.append(data[posi][i])
    #Find index for maximum => Laserpos
    maxarr.append(np.argmax(maximum))

#Distance between the strips as the mean of the differences between the maxima
print("Distance between strips: ", np.mean([maxarr[0]-maxarr[1], maxarr[1]-maxarr[2]]) * 10, "micrometres")
