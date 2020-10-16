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

print(data)
print(data[0][68])

strips = np.arange(0, 128)
position = np.arange(0, 35, 1)
reduposition = np.arange(0, 35, 1)

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
    print(i)
    maximum = []
    for posi in range(0, 35, 1):
        maximum.append(data[posi][i])

        print(data[posi][i])
    #Find index for maximum => Laserpos
    maxarr.append(np.argmax(maximum))
    #print("------------------------")

newposi = []
for i in reduposition:
    newposi.append(data[i][69])

#Distance between the strips as the mean of the differences between the maxima
print("Distance between strips: ", np.mean([maxarr[0]-maxarr[1], maxarr[1]-maxarr[2]]) * 10, "micrometres")



plt.plot(reduposition*10, newposi, marker = 'o',  color = 'black', linestyle = 'None', label="Messwerte")
plt.vlines(10, 0, 170, color = 'orange', linestyle = 'dashed')
plt.vlines(110, 0, 170, color = 'orange', linestyle = 'dashed')
plt.vlines(65, 0, 170, color = 'red', linestyle = 'dashed')
plt.legend()
plt.grid()
plt.xlabel("Position in micrometre")
plt.ylabel("ADC")
plt.savefig("plots/lazorausdehnung.pdf")
plt.clf()
