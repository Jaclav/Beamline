#!/bin/python3
import matplotlib.pyplot as plt
import sys
import statistics as st
import numpy as np
import matplotlib.colors as mcolors

detector = sys.argv[2]
value = str(sys.argv[3])
units = str(sys.argv[4])
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
        if l[0] != "#":
            row = l.split(";")
            if row[6] != "nu_mu" and row[7] == detector + "\n":
                mass.append(row[0])
                charge.append(row[1])
                energy.append(row[5])
                name.append(row[6])
                if not row[6] in others.keys() and not row[6] in main:
                    others[row[6]] = ""
        l = f.readline()


def draw(particleName, clr):
    Colors = {"-1": "darkred", "0": "darkgreen", "1": "darkblue", "2": "violet"}
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
    counts, bins = np.histogram(data, bins=1000)
    if clr == "":
        clr = Colors[str(int(round(float(ch), 0)))]
    ax.stairs(counts, bins, color=clr, label=particleName)
    return data


string = ""
string += (
    "Mode "
    + value
    + " for protons: "
    + str(round(st.mode(draw("proton", "blue")), 3))
    + units
    + "\n"
)
string += (
    "Mode "
    + value
    + " for neutrons: "
    + str(round(st.mode(draw("neutron", "lime")), 3))
    + units
    + "\n"
)
string += (
    "Mode "
    + value
    + " for electrons: "
    + str(round(st.mode(draw("e-", "red")), 3))
    + units
)
print(string)
print(others)
for o in others:
    draw(o, others[o])

ax.set_xlabel("Out " + value + " [" + units + "]", size=20)
ax.set_ylabel("Counts", size=20)
ax.legend(loc="upper center")
ax.set_title(sys.argv[1] + detector + "\n" + string, size=18)
ax.minorticks_on()
ax.set_yscale("log")

plt.show()
