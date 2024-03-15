from math import *
import matplotlib.pyplot as plt
import sys

f = open(sys.argv[1], "r")
str = f.readline()
print(str)

Quantity = {
    "n": 0,
    "γ": 0,
    "p": 0,
    "e": 0,
    "π+-": 0,
    "π0": 0,
    "η'": 0,
    "η": 0,
    "D": 0,
    "K0": 0,
    "K+-": 0,
    "Σ0": 0,
    "Λ": 0,
    "T": 0,
    "Σ+": 0,
    "Σ-": 0,
    "He3": 0,
}


def Name(mass):
    Names = {
        "0": "γ",
        "0.510999": "e",
        "134.977": "π0",
        "139.57": "π+-",
        "938.272": "p",
        "939.565": "n",
        "957.78": "η'",
        "547.862": "η",
        "1875.61": "D",
        "497.614": "K0",
        "1192.64": "Σ0",
        "1189.37": "Σ+",
        "1197.45": "Σ-",
        "1115.68": "Λ",
        "493.677": "K+-",
        "2808.92": "T",
        "2808.39": "He3",
    }
    Quantity[Names[mass]] += 1
    return Names[mass]


Colors = {"-1": "red", "0": "green", "1": "blue", "2": "cyan"}

fig, ax = plt.subplots()
plt.xlabel("X")
plt.ylabel("Y")
plt.xlim(-500, 500)
plt.ylim(-500, 500)

while not str == "":
    str = f.readline()
    if str == "":
        break
    if str[0] == "#":
        continue

    mass = str[: str.find(";")]
    str = str[str.find(";") + 1 :]
    charge = str[: str.find(";")]
    str = str[str.find(";") + 1 :]
    X = str[: str.find(";")]
    str = str[str.find(";") + 1 :]
    Y = str[: str.find(";")]
    str = str[str.find(";") + 1 :]
    Z = str[: str.find(";")]
    str = str[str.find(";") + 1 :]
    E = str[: str.find(";")]

    plt.scatter([float(X)], [float(Z)], color=Colors[charge])
    ax.annotate(Name(mass), (float(X), float(Z)), fontsize=10)

plt.gca().legend(("-", "0", "+"))
leg = ax.get_legend()
leg.legendHandles[0].set_color("red")
leg.legendHandles[1].set_color("green")
leg.legendHandles[2].set_color("blue")

print(Quantity)

plt.show()
