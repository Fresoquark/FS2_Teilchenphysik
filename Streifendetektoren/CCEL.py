import numpy as np
from matplotlib import pyplot as plt
from numpy.random import normal
import os
from scipy import constants
from scipy import optimize
from scipy.constants import elementary_charge

Spannung_liste = [0,10,20,30,40,50,60,70,80,90,100,110,120,130,140,150,160,170,180,190,200]
mean = []

for i in Spannung_liste:
    signal = np.genfromtxt("Data/CCEL/{}CCEL.txt".format(i), unpack = True)
    mean.append(np.mean(signal))

a = 0.00864769757886111
b = 0.0001310540826792737
c = 2.0147268211332093e-05
d = -1.4001913507631864e-07
e = 3.474112787015162e-10

dicke = 300*10**(-6)# 300 meter
depletionsSpannung = 75 # volt

norm = mean / max(mean)

def U_dep(D, u_dep, x):
    if x < u_dep:
        return D * np.sqrt(x / u_dep)
    else:
        return D

spann = []
for u in Spannung_liste:
    spann.append(U_dep(dicke, depletionsSpannung, u))


def fit_func(spann, a):
    return (1 - np.exp(-np.array(spann) / a)) / (1 - np.exp(-300*10**(-6) / a))

params, params_covariance = optimize.curve_fit(fit_func, spann, norm)

print("#####################################################################################")
print("Parameter a: ", params[0]*10**6, ' micrometer plus/minus', params_covariance[0][0]*10**6)
# print("Parameter a: ", params[1], 'micrometer')
print("#####################################################################################")

plt.plot(Spannung_liste, norm, marker = '.',  color = 'magenta', linestyle = 'None', label='Mittelwerte laser')
plt.plot(Spannung_liste, fit_func(spann, *params), label='CCE', color = "dodgerblue", linewidth = 2.0)
plt.grid()
plt.legend()
plt.xlabel('Spannung')
plt.ylabel('CCEL')
plt.savefig('plots/CCEL.pdf')
'''
Parameter a:  194.53707349139205  micrometer
'''
