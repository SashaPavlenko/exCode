import numpy as np
import sympy as sy
import pprint
import matplotlib.pyplot as plt
import seminal_2 as sem

def get_x(l, n):
    x = sy.Symbol('x')
    prod = 1
    for i in range(n):
        prod *= x - l[i][0]
    return prod

def Emita(XY, delta=0.5, do_plot=False, retern_points=False, divided_differenses=False):
    LenXY = len(XY['x'])

    # Строим матрицу первичных/вторичных/... разностей.
    # Создаем матрицу из нулей размерности [количество точек; 2 (координаты по t и v) + количество точек - 1].
    l = np.zeros((LenXY, 1 + LenXY))
    l = l.transpose()

    # Заносим в первый столбец координаты по t, в второй по v.
    l[0] = XY['x']
    l[1] = XY['f']
    l = l.transpose()

    l = np.vstack((l, np.array([[0, 0, 0, 0]])))
    l = np.hstack((l, np.array([[0, 0, 0, 0]]).transpose()))

    l[[2, 3]] = l[[3, 2]]
    l[2][0] = XY['x'][1]
    l[2][1] = XY['f'][1]


    LenXY = l.shape[0]
    EPS = 1e-6

    for j in range(2, LenXY + 1):
        for i in range(LenXY - j + 1):  # range(LenTV-1 -j+1)
            if j - 1 == 1 and abs(l[i + 1][0] - l[i][0]) < EPS:
                l[i][j] = XY['df'][i]
            else:
                l[i][j] = round(l[i + 1][j - 1] - l[i][j - 1], 4) / (l[i + j - 1][0] - l[i][0])

    if divided_differenses:
        return l

    x = sy.symbols('x')
    N = 0
    n = sy.symbols('n')
    for i in range(1, l.shape[1]):
        y = l[0][i]
        N += y * get_x(l, i - 1)

    sy.pprint(N)

    N = sy.simplify(N)

    x_points = np.arange(XY['x'][0]-delta, XY['x'][-1]+delta, 0.1)
    y_points = list(map(lambda i: N.subs(x, i), x_points))

    if do_plot:
        p1 = plt.plot(XY['x'], XY['f'], 'ro')
        p2 = plt.plot(x_points, y_points)
        plt.show()

    if retern_points:
        return N, (x_points, y_points)
    else:
        return N


def Nuton(TV, delta=0.5, do_plot=False, retern_points=False):
    x_star = 3.34
    LenTV = len(TV['t'])

    # Строим матрицу первичных/вторичных/... разностей.
    # Создаем матрицу из нулей размерности [количество точек; 2 (координаты по t и v) + количество точек - 1].
    l = np.zeros((LenTV, 1 + LenTV))
    l = l.transpose()

    # Заносим в первый столбец координаты по t, в второй по v.
    l[0] = TV['t']
    l[1] = TV['v']
    l = l.transpose()

    for j in range(2, LenTV + 1):
        for i in range(LenTV - j + 1):  # range(LenTV-1 -j+1)
            l[i][j] = round(l[i + 1][j - 1] - l[i][j - 1], 4)
    # Матрица первичных/вторичных/... разностей построена.

    x = sy.symbols('x')
    h = l[1][0] - l[0][0]
    t = (x - l[-1][0]) / h


    N = 0
    n = sy.symbols('n')
    for i in range(LenTV):
        y = l[LenTV - i - 1][i + 1]
        N += y * sy.product(t + n, (n, 0, i - 1)) / sy.factorial(i)

    N = sy.simplify(N)

    x_points = np.arange(TV['t'][0] - delta, TV['t'][-1] + delta, 0.1)
    y_points = list(map(lambda i: N.subs(x, i), x_points))

    if do_plot:
        p1 = plt.plot(TV['t'], TV['v'], 'ro')
        p2 = plt.plot(x_points, y_points)
        p3 = plt.plot(x_star, N.subs(x, x_star), '*', markersize=20)
        plt.show()

    if retern_points:
        return N, (x_points, y_points)
    else:
        return N
