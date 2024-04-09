#!/bin/python3
import matplotlib.pyplot as plt
import math
import sys
import statistics as st
import numpy as np
import matplotlib.colors as mcolors

detector = sys.argv[2]
value = str(sys.argv[3])
units = ""
var = ""
if value == "Energy":
    units = "MeV"
    var = "E\u2096"
elif value == "Momentum":
    units = "GeV/c"
    var = "p"
elif value == "Velocity":
    units = "c"
    var = "v"

main = [
    "e-",
    "proton",
    "neutron",
]
others = {
    "nu_mu": "olivedrab",
    "gamma": "yellow",
}

fig = plt.figure()
ax = fig.add_subplot()

mass = []
energy = []
name = []
charge = []
with open(sys.argv[1]) as f:
    l = f.readline()
    while l != "":
        l = l[: len(l) - 1]
        if l[0] != "#":
            row = l.split(";")
            if row[6] != "nu_mu" and row[7] == detector:
                mass.append(row[0])
                charge.append(row[1])
                energy.append(row[5])
                name.append(row[6])
                if not row[6] in others.keys() and not row[6] in main:
                    others[row[6]] = ""
        l = f.readline()


def draw(particleName, clr):
    Colors = {"-1": "tomato", "0": "forestgreen", "1": "lightcyan", "2": "violet"}
    data = []
    ch = "0"
    for i in range(len(name)):
        if name[i] == particleName:
            ch = str(charge[i])
            T = float(energy[i])
            m = float(mass[i])
            if value == "Energy":
                data.append(T)
            elif value == "Momentum":
                data.append(((T + m) ** 2 - m**2) ** 0.5)
            elif value == "Velocity":
                data.append((1 - (m / (T + m)) ** 2) ** 0.5)

    data.sort()
    counts, bins = np.histogram(data, bins=200)
    if clr == "":
        clr = Colors[str(int(round(float(ch), 0)))]
    if value == "Energy":
        logbins = np.logspace(np.log10(bins[0]), np.log10(bins[-1]), len(bins))
        if math.isnan(logbins[0]):
            logbins = bins
        bins = logbins

    counts = list(counts)
    counts.append(counts[-1])
    return counts, bins, data


c, b, d1 = draw("proton", "blue")
c2, b2, d2 = draw("neutron", "lime")
c3, b3, d3 = draw("e-", "red")

string = ""
string += "Mode " + value + " for protons: " + str(round(st.mode(d1), 3)) + units + "\n"
string += (
    "Mode " + value + " for neutrons: " + str(round(st.mode(d2), 3)) + units + "\n"
)
string += "Mode " + value + " for electrons: " + str(round(st.mode(d3), 3)) + units
print(string)
print(others)

ax.set_xlabel("Out " + value + " (" + var + ") [" + units + "]", size=18)
ax.set_ylabel("Counts", size=18)
ax.set_title(detector + "\n" + string, size=10)
ax.minorticks_on()

if value == "Energy":
    ax.minorticks_on()
    # plt.stackplot(
    #     b3, [c3, b3], labels=["e-"], colors=["red"], baseline="weighted_wiggle"
    # )
    # plt.stackplot(b, [c, b], labels=["p"], colors=["blue"], baseline="weighted_wiggle")
    # plt.stackplot(
    #     b2, [c2, b2], labels=["n"], colors=["lime"], baseline="weighted_wiggle"
    # )
    ax.set_yscale("log")
    ax.set_xscale("log")
    ax.stairs(c[0:-1], b, color="blue", label="proton")
    ax.stairs(c2[0:-1], b2, color="lime", label="neutron")
    ax.stairs(c3[0:-1], b3, color="red", label="e-")
    ax.set_xlim([10 ** (-4.1), 10 ** (4.1)])
else:
    ax.stairs(c[0:-1], b, color="blue", label="proton")
    ax.stairs(c2[0:-1], b2, color="lime", label="neutron")
    ax.stairs(c3[0:-1], b3, color="red", label="e-")
    ax.set_xlim([0, 1.05])

ax.legend(loc="upper center", ncol=4)
plt.tight_layout()
plt.savefig("plots/Counts" + value + detector + ".png")
# plt.show()
