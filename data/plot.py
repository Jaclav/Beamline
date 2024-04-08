#!/bin/python3
import statistics as stat
from math import *
import matplotlib.pyplot as plt
import sys

element = sys.argv[1]
if element == "Fe":
    import Fe.data as through
elif element == "Pb":
    import Pb.data as through
    from Pb.spallatedN import *
elif element == "Bi":
    import Bi.data as through
elif element == "Sn":
    import Sn.data as through
    from Sn.spallatedN import *
elif element == "W":
    import W.data as through


tab = {
    0.5: "black",
    0.7: "dimgrey",
    1: "silver",
    1.5: "maroon",
    2: "sienna",
    3: "red",
    4: "salmon",
    5: "orange",
    6: "yellow",
    7: "olive",
    8: "lime",
    9: "green",
    10: "cyan",
    11: "royalblue",
    12: "blue",
    13: "violet",
    14: "magenta",
    15: "purple",
}


def plot(data, energy):
    totalCounts = {}
    for i in data.keys():
        totalCounts[i] = (data[i][0] * 2 + data[i][1] * pi / atan(15 / 15)) / (
            100000  # - through.counts[energy][i][0]
        )
    plt.plot(
        data.keys(),
        totalCounts.values(),
        label=str(energy) + "GeV",
        color=tab[energy],
    )


for en in reversed(list(counts.keys())):
    plot(counts[en], en)
plt.legend(loc="upper left", prop={"size": 13}, ncol=2)
plt.xlabel("Sample length (L) [cm]", size=30)
plt.ylabel("proportion n/p", size=30)
plt.title(element, size=40)
plt.show()
