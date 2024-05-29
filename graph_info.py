

v = 0
for i in range(120):
    try:
        with open(f"vertex{i}.csv", "r") as f:
            txt = f.read()
            v += int(txt.split(",")[1])
    except:
        ...
print(v/2)

E = v
V = 120
from math import log2
print("VlogV:", V*log2(V), "E:", E)
print("V*E: ", V*E)
print("V^2: ", V**2)
