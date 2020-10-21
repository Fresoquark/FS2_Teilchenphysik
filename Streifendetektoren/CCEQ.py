import numpy as np
from matplotlib import pyplot as plt
from numpy.random import normal
import os

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

#Einzelnd, so geht es auf jeden Fall, sollte jetzt etwas kaputt gehen
#with open('Data/CCEQ/0_Cluster_adc_entries.txt', 'r') as file_0:
#    next(file_0)
#    for line in file_0:
#        line.replace(',', '.')
#        array_0V.append(sum(map(float, line.split())))
#

voltages = []
means = []

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
            means.append(np.mean(temporary))            



#####################################################################################
#Die Params haben die Dimension MeV
#Das Polynom der Form: a + bx + cx**2 + dx**3 + ex**4 besitzt die folgenden Parameter:
#Parameter a:  0.00864769757886111
#Parameter b:  0.0001310540826792737
#Parameter c:  2.0147268211332093e-05
#Parameter d:  -1.4001913507631864e-07
#Parameter e:  3.474112787015162e-10
#####################################################################################


a = 0.00864769757886111
b = 0.0001310540826792737
c = 2.0147268211332093e-05
d = -1.4001913507631864e-07
e = 3.474112787015162e-10

umrechnung = []

for i in means: 
    calc = a + b* i + c* i**2 + d* i**3 + e* i**4
    umrechnung.append(calc)
umrechnung = np.sort(umrechnung)
spannung = np.arange(0,210,10)


plt.plot(spannung, umrechnung, marker = '.',  color = 'magenta', linestyle = 'None', label="Energien für Quelle")
plt.legend()
plt.grid()
plt.xlabel("Spannung in V")
plt.ylabel("Energie in MeV")
plt.savefig("plots/CCEQuelleenergie.pdf")
plt.clf()

CCEQ = []

for i in umrechnung:
    CCEQe = i / 0.11395334577499346
    CCEQ.append(CCEQe)

print(CCEQ)

plt.plot(spannung, CCEQ, marker = '.',  color = 'magenta', linestyle = 'None', label="CCEQ für Quelle")
plt.legend()
plt.grid()
plt.xlabel("Spannung in V")
plt.ylabel("Charge Collection Efficiency")
plt.savefig("plots/CCEQuelle.pdf")
plt.clf()