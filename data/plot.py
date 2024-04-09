#!/bin/python3
import statistics as stat
from math import *
import matplotlib.pyplot as plt
import sys

element = sys.argv[1]
if element == "Fe":
    import Fe.through as through
    from Fe.spallatedN import *
elif element == "Pb":
    import Pb.through as through
    from Pb.spallatedN import *
elif element == "Bi":
    import Bi.through as through
    from Bi.spallatedN import *
elif element == "Sn":
    import Sn.through as through
    from Sn.spallatedN import *
elif element == "W":
    import W.through as through
    from W.spallatedN import *
elif element == "Si":
    import Si.through as through
    from Si.spallatedN import *

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

fig = plt.figure()
ax = fig.add_subplot()


def plot(data, energy):
    totalCounts = {}
    for i in data.keys():
        totalCounts[i] = (data[i][0] * 2 + data[i][1] * pi / atan(15 / 15)) / (
            100000  # - through.counts[energy][i][0]
        )
    ax.plot(
        data.keys(),
        totalCounts.values(),
        label=str(energy) + "GeV",
        color=tab[energy],
    )


for en in reversed(list(counts.keys())):
    plot(counts[en], en)

ax.legend(prop={"size": 9})
ax.set_xlabel("sample length ($L$) [cm]", size=14)
ax.set_ylabel("proportion ($n/p_r$)", size=14)
ax.set_title(element, size=20)
ax.set_xlim([5, 36])
fig.tight_layout()
fig.savefig("plots/np(L)" + element + ".png")
# plt.show()
