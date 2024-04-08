#!/bin/python3
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

    plt.scatter([float(X)], [float(Y)], color=Colors[charge])
    ax.annotate(Name(mass) + E, (float(X), float(Y)), fontsize=10)

plt.gca().legend(("-", "0", "+"))
leg = ax.get_legend()
leg.legendHandles[0].set_color("red")
leg.legendHandles[1].set_color("green")
leg.legendHandles[2].set_color("blue")

print(Quantity)

plt.show()
#Minimal energy:326.
0.5:{
},
#Minimal energy:456.39999999999998
0.7:{
},
#Minimal energy:652.
1:{
},
#Minimal energy:6520.0000000000009
10:{
},
#Minimal energy:7172.0000000000009
11:{
},
#Minimal energy:7824.
12:{
},
#Minimal energy:8476.
13:{
},
#Minimal energy:9128.
14:{
},
#Minimal energy:978.
1.5:{
},
#Minimal energy:9780.0000000000018
15:{
},
#Minimal energy:1304.
2:{
},
#Minimal energy:1956.
3:{
},
#Minimal energy:2608.
4:{
},
#Minimal energy:3260.0000000000005
5:{
},
#Minimal energy:3912.
6:{
},
#Minimal energy:4564.
7:{
},
#Minimal energy:5216.
8:{
},
#Minimal energy:5868.
9:{
},
#Minimal energy:326.
0.5:{
5:[76994,3 ],
10:[9911,3 ],
15:[296,4 ],
20:[306,8 ],
25:[255,13 ],
30:[203,29 ],
},
#Minimal energy:456.39999999999998
0.7:{
5:[76478,0 ],
10:[57685,0 ],
15:[41697,0 ],
20:[1276,2 ],
25:[1265,14 ],
30:[1251,30 ],
},
#Minimal energy:652.
1:{
5:[75635,1 ],
10:[57086,1 ],
15:[42798,1 ],
20:[32219,2 ],
25:[10928,7 ],
30:[4011,13 ],
},
#Minimal energy:6520.0000000000009
10:{
5:[76719,0 ],
10:[58865,0 ],
15:[45046,0 ],
20:[34635,0 ],
25:[26522,0 ],
30:[20487,0 ],
},
#Minimal energy:7172.0000000000009
11:{
5:[76605,0 ],
10:[58853,0 ],
15:[44940,0 ],
20:[34529,0 ],
25:[26489,0 ],
30:[20386,0 ],
},
#Minimal energy:7824.
12:{
5:[76624,0 ],
10:[58765,0 ],
15:[44927,0 ],
20:[34483,0 ],
25:[26415,0 ],
30:[20432,0 ],
},
#Minimal energy:8476.
13:{
5:[76545,0 ],
10:[58691,0 ],
15:[44803,0 ],
20:[34475,0 ],
25:[26357,0 ],
30:[20352,0 ],
},
#Minimal energy:9128.
14:{
5:[76456,0 ],
10:[58700,0 ],
15:[44750,0 ],
20:[34364,0 ],
25:[26292,0 ],
30:[20215,0 ],
},
#Minimal energy:978.
1.5:{
5:[75407,0 ],
10:[56818,0 ],
15:[42773,0 ],
20:[32454,2 ],
25:[24988,3 ],
30:[19660,11 ],
},
#Minimal energy:9780.0000000000018
15:{
5:[76435,0 ],
10:[58622,0 ],
15:[44640,0 ],
20:[34322,0 ],
25:[26317,0 ],
30:[20110,0 ],
},
#Minimal energy:1304.
2:{
5:[42651,1 ],
10:[32481,1 ],
15:[24875,2 ],
20:[19412,5 ],
25:[75357,1 ],
30:[56776,1 ],
},
#Minimal energy:1956.
3:{
5:[75520,0 ],
10:[57132,0 ],
15:[42968,0 ],
20:[32822,0 ],
25:[