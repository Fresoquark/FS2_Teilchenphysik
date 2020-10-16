import numpy as np
import matplotlib.pyplot as plt 
import os

clustersize = np.genfromtxt('Data/cluster_size.txt', unpack=True)

Kanalnummer = np.arange(0,128,1)

plt.plot(Kanalnummer[:20], clustersize[:20], marker = '.',  color = 'magenta', linestyle = 'None', label="Clusterhäufigkeit pro Event")
plt.legend()
plt.grid()
plt.xlabel("Kanal")
plt.ylabel("Häufigkeit")
plt.savefig("plots/Clustersize_continuous.pdf")
plt.clf()

plt.bar(Kanalnummer[:20], clustersize[:20], label="Clustersize pro Event", color = 'magenta', alpha=0.6)
plt.legend()
plt.grid()
plt.xlabel("Kanal")
plt.ylabel("Häufigkeit")
plt.savefig("plots/Clustersize_hist.pdf")
plt.clf()


file = open("Data/Cluster_adc_entries.txt")

number_of_entries = []

for line in file: 
    entries = line.split()
    number_of_entries.append(len(entries))

plt.hist(number_of_entries, bins=17, range=[0, 16], label="Clustersize aller Kanäle", color = 'magenta', alpha=0.6)
plt.bar(Kanalnummer[:20], clustersize[:20], label="Clustersize pro Event", color = 'magenta', alpha=0.6)
plt.legend()
plt.grid()
plt.xlabel("Kanal")
plt.ylabel("Häufigkeit")
plt.savefig("plots/clustersamount_hist.pdf")
plt.clf()


hitmap = np.genfromtxt('Data/hitmap.txt', unpack=True)
plt.bar(Kanalnummer ,hitmap ,align='center', color = 'magenta')
plt.grid()
plt.xlabel("Kanal")
plt.ylabel("Häufigkeit")
plt.savefig("plots/hitmap.pdf")
plt.clf()


signal, no_entries = np.genfromtxt('Data/signal_quelle.txt', unpack=True, skip_header=1)
plt.plot(signal, no_entries, marker = '.',  color = 'magenta', linestyle = 'None', label="ADC Counts der $^{90}Sr$ Quelle")
plt.xlim(0, 350)
plt.legend()
plt.grid()
plt.xlabel("Kanal")
plt.ylabel("Häufigkeit")
plt.savefig("plots/signal_Quelle.pdf")
plt.clf()


a = 0.00864769757886111
b = 0.0001310540826792737
c = 2.0147268211332093e-05
d = -1.4001913507631864e-07
e = 3.474112787015162e-10

umrechnung = []

for i in signal: 
    calc = a + b* i + c* i**2 + d* i**3 + e* i**4
    umrechnung.append(calc)
umrechnung = np.sort(umrechnung)

plt.plot(umrechnung, no_entries, marker = '.',  color = 'magenta', linestyle = 'None', label="Energiespektrum der $^{90}Sr$ Quelle")
plt.xlim(0, 10)
plt.legend()
plt.grid()
plt.xlabel("Energie in XXX")
plt.ylabel("Häufigkeit")
plt.savefig("plots/signal_Quelle_energie.pdf")
plt.clf()