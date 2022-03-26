import sympy as sy
import math
from sympy import cos, sqrt, pprint
from lab5 import funcs

x = sy.Symbol('x')
y = sy.Symbol('y')

func = 2*x*(x*x+y)
f = lambda x0, y0: func.subs(x, x0).subs(y,y0)

a, b = 1, 1.1
# n = 10
y0 = sy.exp(1)-2
EPS = 1e-5

y_check = -x*x+sy.exp(x*x)-1
f_exact = lambda val: (y_check).subs(x, val)

for n in [10, 100, 500]:
    ans = funcs.evaluated_values(f, y0, a, b, n, EPS)

    x_ex, y_ex = ans['explicit']
    x_im, y_im = ans['implicit']
    x_heun, y_heun = ans['Heun']
    x_runge, y_runge = ans['Runge']

    d = funcs.my_print(n, x_ex, funcs.insert_values_to_func(f_exact, x_ex), y_ex, y_im, y_heun, y_runge, EPS=EPS)

    norms = [
        funcs.eval_norm(x_ex, y_ex, f_exact),
        funcs.eval_norm(x_im, y_im, f_exact),
        funcs.eval_norm(x_heun, y_heun, f_exact),
        funcs.eval_norm(x_runge, y_runge, f_exact),
    ]

    out = """
    Тесты для n = {n}
    Погрешность явного метода Эйлера: {:e}
    Погрешность неявного метода Эйлера: {:e}
    Погрешность метода Хойна: {:e}
    Погрешность метода Рунге-Кутта: {:e}
    """.format(n=n, *norms)

    print(out)
