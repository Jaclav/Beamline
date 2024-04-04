import statistics as stat
from math import *

d = 11.34
M = 207.217
Na = 6.02214076e23
N = Na * d / M

# tab2 = {
#     5: [216118, 326394],
#     10: [441019, 693798],
#     15: [640990, 1011788],
#     20: [805213, 1253661],
#     25: [933152, 1424409],
#     30: [1036587, 1534304],
# }
tab2 = {
    5: [76045, 0],
    10: [57894, 0],
    15: [43876, 0],
    20: [33662, 0],
    25: [25569, 0],
    30: [19473, 0],
}
# tab = {5: 542512, 10: 1134817, 15: 1652778, 20: 2058874, 25: 2357561, 30: 2570891}
tab = {}
for i in tab2.keys():
    tab[i] = tab2[i][0] + tab2[i][1] * pi / atan(15 / 10)


def cross(x1, x2):
    n1 = tab[x1]
    n2 = tab[x2]

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


def cross2(i):
    return -1 / (i * N) * log(tab[i] / 100000)


# crosses = []
# for i in [5, 10, 15, 20, 25, 30]:
#     for j in [5, 10, 15, 20, 25, 30]:
#         if j > i:
#             print(i, j, cross(i, j) * 10**24)
#             crosses.append(cross(i, j) * 10**24)
# print(stat.mean(crosses))

crosses = []
for i in [5, 10, 15, 20, 25, 30]:
    crosses.append(cross2(i) * 10**24)
print(stat.mean(crosses))

# Ideal: 1 370 796
# perp 216118
# para 326394
# Jacek: 1 259 467
