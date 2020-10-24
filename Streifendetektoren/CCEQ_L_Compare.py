import numpy as np
from matplotlib import pyplot as plt
from numpy.random import normal
import os
from scipy import constants
from scipy import optimize
from scipy.constants import elementary_charge

##CCEQ
array_0 = []
array_10 = []
array_20 = []
array_30 = []
array_40 = []
array_50 = []
array_60 = []
array_70 = []
array_80 = []
array_90 = []
array_100 = []
array_110 = []
array_120 = []
array_130 = []
array_140 = []
array_150 = []
array_160 = []
array_170 = []
array_180 = []
array_190 = []
array_200 = []


voltages = []
means_Q = []

Path = "Data/CCEQ/"
filelist = os.listdir(Path)
for i in filelist: 
    if i.endswith(".txt"):
        onlynumbers = i
        onlynumbers = onlynumbers.replace('_Cluster_adc_entries.txt', '')
        x = onlynumbers
        voltages.append(x)
        with open(Path + i, 'r') as f:
            next(f)
            temporary = []
            for line in f: 
                line.replace(',', '.')
                temporary.append(sum(map(float, line.split())))
            means_Q.append(np.mean(temporary))            


a = 0.00864769757886111
b = 0.0001310540826792737
c = 2.0147268211332093e-05
d = -1.4001913507631864e-07
e = 3.474112787015162e-10

umrechnung_Q = []

for i in means_Q: 
    calc = a + b* i + c* i**2 + d* i**3 + e* i**4
    umrechnung_Q.append(calc)


umrechnung_Q = np.sort(umrechnung_Q)

CCEQ = []

for i in umrechnung_Q:
    CCEQe = i / np.max(umrechnung_Q)
    CCEQ.append(CCEQe)

#CCEL

Spannung_liste = [0,10,20,30,40,50,60,70,80,90,100,110,120,130,140,150,160,170,180,190,200]
mean_L = []

for i in Spannung_liste:
    signal_L = np.genfromtxt("Data/CCEL/{}CCEL.txt".format(i), unpack = True)
    mean_L.append(np.mean(signal_L))

norm = mean_L / max(mean_L)


plt.plot(Spannung_liste, norm, marker = '.',  color = 'dodgerblue', linestyle = 'None', label='Mittelwerte laser')
plt.plot(Spannung_liste, CCEQ, marker = '.',  color = 'magenta', linestyle = 'None', label="CCEQ für Quelle")
plt.legend()
plt.grid()
plt.xlabel("Spannung in V")
plt.ylabel("Charge Collection Efficiency")
plt.savefig("plots/CCEQuelle_Laser.pdf")
plt.clf()