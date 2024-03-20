#!/usr/bin/env python3
# calculate cross section for Lead 208
from math import *

dPb = 11340  # lead density kg/m^3
NA = 6.0221415e23  # avogadro constant
mu = 207.217e-3  # kg/mol

dN = NA * dPb / mu  # density of number of lead nuclei in bar

p0 = 10000
C = 925060 / p0  # 10GeV

# cross section of lead nuclei for interaction with  electron source: Orear Physics vol. 2
R = 7.5e-15
print("σ\u2091\u208B=" + str(pi * R**2))

# cross section of lead nuclei for interaction with proton from our simulation data
x = 0.25
Nn = 635183
print("σ\u209A\u208A=" + str(1 / (dN * x) * log((p0 * C) / (p0 * C - Nn))))

# cross section of lead nuclei as non interacting ball source: https://inspirehep.net/files/8cb839c04600858cdde2de6640a11bbc
print(
    "S="
    + str((pi * (5.56e-15) ** 2) * 10 ** (-floor(log10(pi * (5.56e-15) ** 2))) / 10)
    + "e-28"
)

# dla porównania https://sci-hub.st/https://doi.org/10.1016/j.physletb.2016.06.027
