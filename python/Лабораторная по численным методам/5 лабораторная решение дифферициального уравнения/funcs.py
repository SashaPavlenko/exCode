import sympy as sy
import numpy as np
import pandas as pd
import math

from math import sqrt
from sympy import cos, sqrt, pprint


def explicit_Euler(func, y0, a, b, n, EPS=1e-5):
    """
    :param func: лямбда-функция
    :param y0: f(x0,y0)
    :param a:
    :param b:
    :param n:
    :return: Интервалы x и y
    """
    h = (b - a) / n
    x = np.arange(a, b, h)
    y = [y0.evalf()]

    for i in range(1, n):
        val = y[i - 1] + h * func(x[i - 1], y[i - 1])

        y.append(val)

    y = np.array(y)

    return (x, y)


def implicit_Euler(func, y0, a, b, n, EPS=1e-5):
    h = (b - a) / n
    x = np.arange(a, b, h)
    y = [y0.evalf()]

    for i in range(1, n):
        y_tilda = y[i-1] + h*func(x[i-1], y[i-1])
        val = y[i - 1] + h * func(x[i], y_tilda)

        y.append(val)

    y = np.array(y)

    return (x, y)


def Heun(func, y0, a, b, n, EPS=1e-5):
    h = (b - a) / n
    x = np.arange(a, b, h)
    y = [y0.evalf()]

    for i in range(1, n):
        y_tilda = y[i - 1] + h * func(x[i - 1], y[i - 1])
        val = y[i - 1] + h / 2 * (func(x[i - 1], y[i-1]) + func(x[i], y_tilda))

        y.append(val)

    y = np.array(y)

    return (x, y)


def find_koef(p2=2/5, p3=2/5):
    p1, a2, a3, b21, b31, b32 = sy.symbols('p1, a2, a3, b21, b31, b32')

    p2_copy = p2
    p3_copy = p3

    p2 = sy.Symbol(str(p2))
    p3 = sy.Symbol(str(p3))

    sets = [
        p3*a3 + p2*a2 - 0.5,
        p2 + p3 + p1 - 1,
        a2 - b21,
        a3 - (b31 + b32),
        -a2*b32*(2 - 3*a2) + a3*(-a2 + a3) - 0,
        p3*a2*b32 - 1/6

    ]

    ans = sy.solvers.solve(sets, [p1, a2, a3, b21, b31, b32])

    ans = list(map(lambda x: eval(str(x.evalf())), [*ans[0]]))
    ans = [ans[0]] + [p2_copy, p3_copy] + ans[1:]

    return ans


def eval_norm(x, f_numer, f_exact):
    y_ex = insert_values_to_func(f_exact, x)

    l = y_ex - f_numer
    l = l.astype(float)
    delta = np.linalg.norm(l)

    return delta


def insert_values_to_func(f_exact, x, EPS=1e-5):
    y_ex = []
    for i in range(x.shape[0]):
        val = f_exact(x[i])
        y_ex.append(val)

    y_ex = np.array(y_ex)
    return y_ex


def my_print(n, x, exact, explicit, implicit, Heun, Runge, EPS=1e-5, print_out=True):
    nums = int(math.log10(1 / EPS))

    vect = np.vectorize(lambda a: float(a))

    exact = vect(exact)
    explicit = vect(explicit)
    implicit = vect(implicit)
    Heun = vect(Heun)
    Runge = vect(Runge)

    d = {
        'i': np.arange(0, n, 1),
        'x[i]': x,
        'точное': exact,
        'Явный': explicit,
        'Неявный': implicit,
        'Хойне': Heun,
        'Рунге-Кутте': Runge,
    }

    df = pd.DataFrame(data=d)
    pd.set_option("display.precision", nums)

    df2 = df.to_string(index=False)

    if print_out:
        print(df2)

    return df


def system_solve_print(n, x, exact, Runge, EPS=1e-5, print_out=True):
    nums = int(math.log10(1 / EPS))

    vect = np.vectorize(lambda a: float(a))

    exact = vect(exact)
    Runge = vect(Runge)

    d = {
        'i': np.arange(0, n, 1),
        'x[i]': x,
        'точное': exact,
        'Рунге-Кутте': Runge,
    }

    df = pd.DataFrame(data=d)
    pd.set_option("display.precision", nums)

    df2 = df.to_string(index=False)

    if print_out:
        print(df2)

    return df


def evaluated_values(f, y0, a, b, n, EPS=1e-5):
    x_ex, y_ex = explicit_Euler(f, y0, a, b, n, EPS=EPS)
    x_im, y_im = implicit_Euler(f, y0, a, b, n, EPS=EPS)
    x_heun, y_heun = Heun(f, y0, a, b, n, EPS=EPS)
    x_runge, y_runge = Runge(f, y0, a, b, n, EPS=EPS)

    ans = {
        'explicit': (x_ex, y_ex),
        'implicit': (x_im, y_im),
        'Heun': (x_heun, y_heun),
        'Runge': (x_runge, y_runge),
    }

    return ans


def Runge(func, y0, a, b, n, EPS=1e-5, p2=2/5, p3=2/5):
    h = (b - a) / n
    x = np.arange(a, b, h)
    y = [y0.evalf()]

    p1, p2, p3, a2, a3, b21, b31, b32 = find_koef(p2, p3)

    K1 = lambda x_i, y_i: h*func(x_i, y_i)
    K2 = lambda x_i, y_i: h*func(x_i + a2*h, y_i + b21*K1(x_i, y_i))
    K3 = lambda x_i, y_i: h*func(x_i + a3*h, y_i + b31*K1(x_i, y_i) + b32*K2(x_i, y_i))


    for i in range(1, n):
        val = y[i-1] + p1*K1(x[i-1], y[i-1]) + p2*K2(x[i-1], y[i-1]) + p3*K3(x[i-1], y[i-1])

        y.append(val)

    y = np.array(y)

    return (x, y)


def Runge_system(func, y0, a, b, n, EPS=1e-5, p2=2/5, p3=2/5):
    h = (b - a) / n
    x = np.linspace(a, b, n)

    p1, p2, p3, a2, a3, b21, b31, b32 = find_koef(p2, p3)

    print(p1, p2, p3, a2, a3, b21, b31, b32)

    K1 = lambda x_i, y_i, z_i, u_i, num: \
        h*func(
            x_i,
            y_i,
            z_i,
            u_i,
            num,
    )

    K2 = lambda x_i, y_i, z_i, u_i, num: \
        h*func(
            x_i + a2*h,
            y_i + b21*K1(x_i, y_i, z_i, u_i, 0),
            z_i + b21*K1(x_i, y_i, z_i, u_i, 1),
            u_i + b21*K1(x_i, y_i, z_i, u_i, 2),
            num
        )

    K3 = lambda x_i, y_i, z_i, u_i, num: \
        h*func(
            x_i + a3*h,
            y_i + b31*K1(x_i, y_i, z_i, u_i, 0) + b32*K2(x_i, y_i, z_i, u_i, 0),
            z_i + b31*K1(x_i, y_i, z_i, u_i, 1) + b32*K2(x_i, y_i, z_i, u_i, 1),
            u_i + b31*K1(x_i, y_i, z_i, u_i, 2) + b32*K2(x_i, y_i, z_i, u_i, 2),
            num,
        )

    ans = {
        'y': [y0[0]],
        'z': [y0[1]],
        'u': [y0[2]],
    }

    for i in range(1, n):
        K = {
            'K1': [
                K1(x[i - 1], ans['y'][i - 1], ans['z'][i - 1], ans['u'][i - 1], 0),
                K1(x[i - 1], ans['y'][i - 1], ans['z'][i - 1], ans['u'][i - 1], 1),
                K1(x[i - 1], ans['y'][i - 1], ans['z'][i - 1], ans['u'][i - 1], 2),
            ],

            'K2': [
                K2(x[i - 1], ans['y'][i - 1], ans['z'][i - 1], ans['u'][i - 1], 0),
                K2(x[i - 1], ans['y'][i - 1], ans['z'][i - 1], ans['u'][i - 1], 1),
                K2(x[i - 1], ans['y'][i - 1], ans['z'][i - 1], ans['u'][i - 1], 2),
            ],

            'K3': [
                K3(x[i - 1], ans['y'][i - 1], ans['z'][i - 1], ans['u'][i - 1], 0),
                K3(x[i - 1], ans['y'][i - 1], ans['z'][i - 1], ans['u'][i - 1], 1),
                K3(x[i - 1], ans['y'][i - 1], ans['z'][i - 1], ans['u'][i - 1], 2),
            ],
        }

        l = []
        keys = {
            0: 'y',
            1: 'z',
            2: 'u',
        }

        for j in range(3):
            val = ans[keys[j]][i - 1] + \
                    p1 * K['K1'][j] + \
                    p2 * K['K2'][j] + \
                    p3 * K['K3'][j]
            l.append(val)

        ans['y'].append(l[0])
        ans['z'].append(l[1])
        ans['u'].append(l[2])

    return x, np.array(ans['y'])