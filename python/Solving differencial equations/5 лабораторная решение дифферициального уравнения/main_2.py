from lab5 import funcs

import sympy as sy
import math
from sympy import cos, sqrt, pprint
from lab5 import funcs

x = sy.Symbol('x')
y = sy.Symbol('y')
z = sy.Symbol('z')
u = sy.Symbol('u')

func = [
    z,
    u,
    ((6*x-7)*u - 4*x*z + 4*y) / (2*x - 3),
]

beg_cond = [
    8.16,
    6.25,
    2.07,
]

f = lambda x0, y0, z0, u0, number: func[number].subs(x, x0).subs(y, y0).subs(z, z0).subs(u, u0)

a, b = 0, 0.75
n = 500
EPS = 1e-5
df = []

y_check = 0.12*x + 10.19*sy.exp(x) - 2.03*sy.exp(2*x)
f_exact = lambda val: (y_check).subs(x, val)

for n in [10]:
    xx, ans = funcs.Runge_system(f, beg_cond, a, b, n, EPS)

    df.append(funcs.system_solve_print(n, xx, funcs.insert_values_to_func(f_exact, xx, EPS), ans, EPS, print_out=False))

    print("Тесты для n = %d\nПогрешность метода Рунге-Кутта: %e" %(n, funcs.eval_norm(xx, ans, f_exact)))

print(df[0])