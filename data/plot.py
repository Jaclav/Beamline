#!/bin/python3
import statistics as stat
from math import *
import matplotlib.pyplot as plt
from sims.spallatedN import *
import sims.protonsThrough as throught


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
        totalCounts[i] = (data[i][0] * 2 + data[i][1] * pi / atan(15 / 10)) / (
            100000 - throught.counts[energy][i]
        )
    plt.plot(
        data.keys(),
        totalCounts.values(),
        label=str(energy) + "GeV",
        color=tab[int(energy)],
    )


for en in reversed(list(counts.keys())):
    plot(counts[en], en)
plt.legend(loc="upper left")
plt.xlabel("L1 [cm]", size=30)
plt.ylabel("n/p", size=30)
plt.title("Number of neutrons by L length", size=40)
plt.show()
