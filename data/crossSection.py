#!/usr/bin/env python3
# calculate cross section for LEAD
from math import *

dPb = 11340  # kg/m^3
NA = 6.0221415e23
mu = 207e-3  # kg/mol

S = 16e-4
L = 0.8
V = L * S

N = NA * dPb * V / mu

p0 = 10000
C = 925060 / p0  # 10GeV

# Przekrój czynny dla elektronu reagującego z ołowiem Orear tom 2
R = 7.5e-15
print("σe=" + str(pi * R**2))

# przekrój czynny dla protonu reagującego z ołowiem
x = 0.25
Nn = 635183
print("σp=" + str((L * S / (N * x)) * log((p0 * C) / (p0 * C - Nn))))

# pole powierzchni poprzecznej ołowiu https://inspirehep.net/files/8cb839c04600858cdde2de6640a11bbc
print(
    "S="
    + str((pi * (5.56e-15) ** 2) * 10 ** (-floor(log10(pi * (5.56e-15) ** 2))) / 10)
    + "e-28"
)

# dla porównania https://sci-hub.st/https://doi.org/10.1016/j.physletb.2016.06.027
