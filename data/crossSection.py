#!/usr/bin/env python3
# calculate cross section for Lead 208
from math import *
import sys

dPb = 11340  # lead density kg/m^3
NA = 6.0221415e23  # avogadro constant
mu = 207.217e-3  # kg/mol
dN = NA * dPb / mu  # density of number of lead nuclei in bar

tab = [
    4262,
    7028,
    10174,
    10512,
    10538,
    12065,
    12604,
    14016,
    13854,
    14491,
    13888,
    14463,
    14503,
    14468,
    14481,
    14404,
    14178,
    13870,
    14387,
    13924,
]


# cross section of lead nuclei for interaction with proton from our simulation data
# n=nMax(1-exp(x/t))
def sigma(nMax, n, x):
    return 1 / (dN * x) * log(nMax / (nMax - n))


suma = 0
for i in range(0, 17):
    print(sigma(15000, tab[i], 5 * (i + 2)))
print(suma / 17)

# cross section of lead nuclei for interaction with  electron source: Orear Physics vol. 2
R = 7.5e-15
print("σ\u2091\u208B=" + str(pi * R**2))

# cross section of lead nuclei as non interacting ball source: https://inspirehep.net/files/8cb839c04600858cdde2de6640a11bbc
print(
    "S="
    + str((pi * (5.56e-15) ** 2) * 10 ** (-floor(log10(pi * (5.56e-15) ** 2))) / 10)
    + "e-28"
)

# dla porównania https://sci-hub.st/https://doi.org/10.1016/j.physletb.2016.06.027
