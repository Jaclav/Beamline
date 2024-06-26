#!/bin/python3
import statistics as stat
from math import *
import matplotlib.pyplot as plt
import sys

"""'
for x in {Bi,Fe,Pb,Si,Sn,W}
do
./crossSections.py $x
done
"""

d = 11.34  # density g/cm3
M = 207.217  # molar mass g/mol
element = sys.argv[1]
if element == "Fe":
    d = 7.874
    M = 55.85
    from Fe.through import *
elif element == "Pb":
    d = 11.34
    M = 207.217
    from Pb.through import *
elif element == "Bi":
    d = 9.78
    M = 208.9804
    from Bi.through import *
elif element == "Sn":
    d = 7.31
    M = 118.71
    from Sn.through import *
elif element == "W":
    d = 19.25
    M = 183.84
    from W.through import *
elif element == "Si":
    d = 2.33
    M = 28.085
    from Si.through import *

Na = 6.02214076e23  # avogadro constant
N = Na * d / M  # number of lead nuclei per volume 1/cm3


def crossSectionByLengths(data):
    totalCounts = {}
    for i in data.keys():
        totalCounts[i] = data[i][0] + data[i][1] * pi / atan(15 / 15)
    crossSec = []
    for i in data.keys():
        crossSec.append(-1 / (i * N) * log(totalCounts[i] / 100000) * 10**24)
    return round(stat.mean(crossSec), 3)


crossSections = []
for en in counts.keys():
    print("σ\u209A\u208A(", en, "GeV)=", crossSectionByLengths(counts[en]), "b")
    crossSections.append(crossSectionByLengths(counts[en]))

fig = plt.figure()
ax = fig.add_subplot()
ax.plot(counts.keys(), crossSections)
ax.scatter(counts.keys(), crossSections)
ax.set_title("σ\u209A in p" + element + " collision", size=30)
ax.set_xlabel("Energy (E\u2096) [GeV]", size=18)
ax.set_ylabel("Cross section (σ\u209A) [b]", size=18)
# ax.set_xscale("log")
ax.minorticks_on()
fig.savefig("plots/crossSection" + element + ".png")
ax.set_xticks([4, 6, 8, 10, 12, 14, 15])
plt.show()

# https://inspirehep.net/files/8cb839c04600858cdde2de6640a11bbc
# https://sci-hub.st/https://doi.org/10.1016/j.physletb.2016.06.027

# Ideal: 1 370 796
# perp 216118
# para 326394
# Jacek: 1 259 467
