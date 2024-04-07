#!/bin/python3
import sys

C = 299.792458
reactions = {}
index = 0
numberOfNeutronsIn = 0
numberOfNeutronsOut = 0
numberOfNeutronsNew = 0


def isIn(num, tab):
    for x in tab:
        if num * 1.008 >= x and num * 0.998 <= x:
            # if x == num:
            return True
    return False


with open(sys.argv[1]) as f:
    l = f.readline()
    data = []
    while l != "":
        if l[0] != "#":
            l = l[: len(l) - 1]
            tab = l.split(";")

            if tab[7] == "detPerp" and tab[6] == "neutron":
                numberOfNeutronsIn += 1
                data.append(float(tab[8]))
                if len(data) > 100:
                    data.pop(0)
            elif tab[7] == "detEnd" and tab[6] == "neutron":
                if isIn(float(tab[8]), data):
                    numberOfNeutronsOut += 1
                else:
                    numberOfNeutronsNew += 1
        l = f.readline()

print("n_0=", numberOfNeutronsIn)
print("n=", numberOfNeutronsOut)
print("n_n=", numberOfNeutronsNew)
