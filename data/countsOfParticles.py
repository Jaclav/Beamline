import matplotlib.pyplot as plt
import random as r
import sys
import numpy as np
import matplotlib.colors as mcolors

particle = "neutron"
(mass, charge, x, y, z, energy, name) = np.loadtxt(
    sys.argv[1], dtype="str", unpack=True, delimiter=";", skiprows=103
)

others = {
    "nu_mu": "olivedrab",
    "gamma": "yellow",
}
for i in name:
    if not i in others.keys() and not i in ["e-", "proton", "neutron"]:
        others[i] = ""


def draw(particleName, clr):
    Colors = {"-1": "darkred", "0": "darkgreen", "1": "darkblue", "2": "violet"}
    momeuntums = []
    ch = "0"
    for i in range(len(name)):
        if name[i] == particleName:
            ch = str(charge[i])
            T = float(energy[i])
            m = float(mass[i])
            # momeuntums.append(((T + m) ** f2 - m**2) ** 0.5)  # momentum
            # momeuntums.append(T)  # energy
            momeuntums.append((1 - (m / (T + m)) ** 2) ** 0.5)  # velocity

    momeuntums.sort()
    ran = [x / 1000 for x in range(1010)]
    counts, bins = np.histogram(momeuntums, bins=ran)
    if clr == "":
        clr = Colors[str(int(round(float(ch), 0)))]
    plt.stairs(counts, bins, color=clr, label=particleName)


draw("e-", "red")
draw("proton", "blue")
draw("neutron", "lime")
print(others)
for o in others:
    draw(o, others[o])

f = open(sys.argv[1])
plt.xlabel("Out velocity(c)")
plt.ylabel("Counts")
plt.legend(loc="upper right")
plt.title(sys.argv[1] + f.readline())
plt.minorticks_on()

plt.show()
