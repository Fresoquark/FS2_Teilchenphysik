import numpy as np
import matplotlib.pyplot as plt
import os

clustersize = np.genfromtxt('Data/cluster_size.txt', unpack=True)

Kanalnummer = np.arange(0,128,1)

plt.plot(Kanalnummer[:6], clustersize[:6], marker = '.',  color = 'magenta', linestyle = 'None', label="Clusterhäufigkeit pro Event")
plt.legend()
plt.grid()
plt.xlabel("Kanal")
plt.ylabel("Häufigkeit")
plt.savefig("plots/Clustersize_continuous.pdf")
plt.clf()

plt.bar(Kanalnummer[:6], clustersize[:6], label="Kanäle pro Cluster", color = 'magenta', alpha=0.6)
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

# N0 = 0
# N1 = 0
# N2 = 0
# N3 = 0
# N4 = 0
# N5 = 0
# N6 = 0
# N7 = 0
# for i in number_of_entries:
#     if i == 0:
#         N0 += 1
#     elif i == 1:
#         N1 += 1
#     elif i == 2:
#         N2 += 1
#     elif i == 3:
#         N3 += 1
#     elif i == 4:
#         N4 += 1
#     elif i == 5:
#         N5 += 1
#     elif i == 6:
#         N6 += 1
#     elif i == 7:
#         N7 += 1

# nums = [N0, N1, N2, N3, N4, N5, N6, N7]

num_of_clus = np.genfromtxt('Data/number_of_clusters.txt', unpack=True)
plt.bar(Kanalnummer[:6], clustersize[:6], label="Kanäle pro Cluster", color = 'magenta', alpha=0.6)
plt.bar(Kanalnummer[:6], num_of_clus[:6], label="Anzahl Cluster Pro Event", color = 'dodgerblue', alpha=0.6)
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
ADC_most_probable = np.argmax(no_entries)
print(np.mean(no_entries[no_entries > 0]))
plt.plot(signal, no_entries, marker = '.',  color = 'magenta', linestyle = 'None', label="ADC Counts der $^{90}Sr$ Quelle")
plt.vlines(signal[ADC_most_probable], 0, np.max(no_entries), color='dodgerblue', linestyle='--')
plt.xlim(30, 250)
plt.legend()
plt.grid()
plt.xlabel("ADC")
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

energy_most_probable = np.argmax(no_entries)
plt.plot(umrechnung, no_entries, marker = '.',  color = 'magenta', linestyle = 'None', label="Energiespektrum der $^{90}Sr$ Quelle")
plt.vlines(umrechnung[energy_most_probable], 0, np.max(no_entries), color='dodgerblue', linestyle='--')
plt.xlim(1.5, 6)
plt.legend()
plt.grid()
plt.xlabel("Energie in keV")
plt.ylabel("Häufigkeit")
plt.savefig("plots/signal_Quelle_energie.pdf")
plt.clf()
