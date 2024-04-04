import statistics as stat
from math import *

d = 11.34  # density g/cm3
M = 207.217  # molar mass g/mol
Na = 6.02214076e23  # avogadro constant
N = Na * d / M  # number of lead nuclei per volume 1/cm3

data = {
    5: [76045, 0],
    10: [57894, 0],
    15: [43876, 0],
    20: [33662, 0],
    25: [25569, 0],
    30: [19473, 0],
}
# data = {5: 542512, 10: 1134817, 15: 1652778, 20: 2058874, 25: 2357561, 30: 2570891}
counts = {}
for i in data.keys():
    counts[i] = data[i][0] + data[i][1] * pi / atan(15 / 10)


def cross(x1, x2):
    n1 = counts[x1]
    n2 = counts[x2]

    return abs(2 / N * (n1 * x2 - n2 * x1) / (n1 * x2**2 - n2 * x1**2))
    k = n1 / n2
    return (
        -1 / 2 * (k * x2**2 - x1**2)
        + abs(
            1 / 4 * (k * x2**2 - x1**2) ** 2
            - 2 / 3 * (x1**3 - k * x2**3) * (x1 - k * x2)
        )
        ** 0.5
    ) / (1 / 3 * N * (x1**3 - k * x2**3))


# crosses = []
# for i in [5, 10, 15, 20, 25, 30]:
#     for j in [5, 10, 15, 20, 25, 30]:
#         if j > i:
#             print(i, j, cross(i, j) * 10**24)
#             crosses.append(cross(i, j) * 10**24)
# print(stat.mean(crosses))
def cross2(i):
    return -1 / (i * N) * log(counts[i] / 100000)


crosses = []
for i in data.keys():
    crosses.append(cross2(i) * 10**24)
print("σ\u209A\u208A=", round(stat.mean(crosses), 3), "b")

# https://inspirehep.net/files/8cb839c04600858cdde2de6640a11bbc
# https://sci-hub.st/https://doi.org/10.1016/j.physletb.2016.06.027

# Ideal: 1 370 796
# perp 216118
# para 326394
# Jacek: 1 259 467
