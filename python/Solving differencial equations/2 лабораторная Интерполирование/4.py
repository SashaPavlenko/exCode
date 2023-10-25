import sympy as sy
from seminal_2 import final

XY = {
    'x': [1, 2, 3],
    'f': [12, 27, 54],
    'df': ['', 20, ''],
}

l = final.Emita(XY, divided_differenses=True)
N = final.Emita(XY)

print(l)

sy.pprint(N)