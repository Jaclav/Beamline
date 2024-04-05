#!/bin/python3
import matplotlib.pyplot as plt
import sys
import statistics as st
import numpy as np
import matplotlib.colors as mcolors

main = [
    "e-",
    "proton",
    "neutron",
]
others = {
    "nu_mu": "olivedrab",
    "gamma": "yellow",
}

mass = []
energy = []
name = []
charge = []
with open(sys.argv[1]) as f:
    l = f.readline()
    while l != "":
        if l[0] != "#":
            row = l.split(";")
            if row[6] != "nu_mu" and row[7] == "detPerp\n":
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
            # momeuntums.append(((T + m) ** f2 - m**2) ** 0.5)  # momentum
            # momeuntums.append(T)  # energy
            data.append((1 - (m / (T + m)) ** 2) ** 0.5)  # velocity

    data.sort()
    ran = [x / 1000 for x in range(1010)]
    counts, bins = np.histogram(data, bins=ran)
    if clr == "":
        clr = Colors[str(int(round(float(ch), 0)))]
    plt.stairs(counts, bins, color=clr, label=particleName)
    return data


draw("e-", "red")
vp = st.mode(draw("proton", "blue"))
print("Most protons have velocity:", round(vp, 3))
print(
    "Most protons have energy:",
    round(938 / (1 - vp**2) ** 0.5 - 938, 3),
)
draw("neutron", "lime")
print(others)
for o in others:
    draw(o, others[o])

plt.xlabel("Out velocity(c)")
plt.ylabel("Counts")
plt.legend(loc="upper center")
plt.title(sys.argv[1] + " perpendicular detector")
plt.minorticks_on()

plt.show()
