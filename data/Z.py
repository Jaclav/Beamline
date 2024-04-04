import sys
from matplotlib import pyplot as plt
import statistics as st
import numpy as np

sum = 0
data = []
index=0
with open(sys.argv[1]) as f:
    l = f.readline()
    while l != "":
        index+=1
        try:
            if l[0] != "#":
                if l.split(";")[6] == "neutron":
                   data.append(float(l.split(";")[4]))
                   sum += 1
            l = f.readline()
        except:
            print(l)
            l = f.readline()
            continue
print(st.mean(data))
print(sum)
counts, bins = np.histogram(data, bins=1000)
plt.stairs(counts, bins)
plt.title(sys.argv[1])
plt.show()
