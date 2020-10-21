import numpy as np
from matplotlib import pyplot as plt
from numpy.random import normal
import os

Spannung_liste = [0,10,20,30,40,50,60,70,80,90,100,110,120,130,140,150,160,170,180,190,200]
mean = []

for i in Spannung_liste:
    signal = np.genfromtxt("{}CCEL.txt".format(i), unpack = True)
    mean.append(np.mean(signal))

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

