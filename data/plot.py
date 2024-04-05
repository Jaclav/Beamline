#!/bin/python3
import statistics as stat
from math import *
import matplotlib.pyplot as plt
from sims.spallatedN import *


def plot(data, energy):
    totalCounts = {}
    for i in data.keys():
        totalCounts[i] = data[i][0] + data[i][1] * pi / atan(15 / 10)
    plt.plot(data.keys(), totalCounts.values(), label=str(energy) + "GeV")


for en in counts.keys():
    plot(counts[en], en)
plt.legend(loc="upper left")
plt.xlabel("L1 [cm]")
plt.ylabel("Number of neutrons")
plt.title("Number of neutrons by L1 length")
plt.show()
