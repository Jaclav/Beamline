#!/bin/python3
import statistics as stat
from math import *
import matplotlib.pyplot as plt
from sims.spallatedN import *


tab = [
    "",
    "black",
    "darkred",
    "red",
    "salmon",
    "orange",
    "yellow",
    "olive",
    "lime",
    "green",
    "cyan",
    "royalblue",
    "blue",
    "violet",
    "magenta",
    "purple",
]


def plot(data, energy):
    totalCounts = {}
    for i in data.keys():
        totalCounts[i] = (
            data[i][0] * 2 + data[i][1] * pi / atan(15 / 10)
        ) / 100000  # in this case we may assume that all protons react, Delta is small
    plt.plot(
        data.keys(),
        totalCounts.values(),
        label=str(energy) + "GeV",
        color=tab[int(energy)],
    )


for en in reversed(list(counts.keys())):
    plot(counts[en], en)
plt.legend(loc="upper left")
plt.xlabel("L1 [cm]")
plt.ylabel("Number of neutrons per reaction")
plt.title("Number of neutrons by L1 length")
plt.show()
