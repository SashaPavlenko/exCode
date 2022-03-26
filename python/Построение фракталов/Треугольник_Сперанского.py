import random
from turtle import *


def fill_circle(r, phi=360, color='black'):
    t.begin_fill()
    t.fillcolor(color)
    t.circle(r, phi)
    t.end_fill()

def do_new_point(point_one: tuple, point_two: tuple) -> tuple:
    return point_one[0] + (point_two[0] - point_one[0]) * (1/2), point_one[1] + (point_two[1] - point_one[1]) * (1/2)


t = Turtle()
t.speed(6)
t.up()
# Turtle.hideturtle()
t.hideturtle()

t.screen.setup(800, 600)

start_point = (
    # Псевдорандом расположения стартовых точек для нормальной формы треугольника.
    (random.randint(-400, 0), random.randint(-150, 50)),
    (random.randint(0, 400), random.randint(-150, 50)),
    (random.randint(-400, 400), random.randint(150, 300)),

    # Точки в абсолютно рандомных местах.
    # (random.randint(-400, 400), random.randint(-300, 300)),
    # (random.randint(400, 400), random.randint(-300, 300)),
    # (random.randint(-400, 400), random.randint(300, 300)),
)

t.goto(start_point[0])
fill_circle(5, color='red')
t.goto(start_point[1])
fill_circle(5, color='red')
t.goto(start_point[2])
fill_circle(5, color='red')

now_point = (random.randint(-50, 50), random.randint(-300, 300))

t.goto(now_point)
fill_circle(3, color='orange')


# number_of_point = 1000
number_of_point = 2000
increase_speed = 5

for i in range(number_of_point):
    n = random.randint(0, 2)
    now_point = do_new_point(now_point, start_point[n])

#     print(f'''\
# ____________________________
# now_point = {now_point}
# start_point[{n}] = {star_point[n]}
# do_new_point = {do_new_point(now_point, star_point[n])}
# ____________________________
# ''')

    t.goto(now_point)
    fill_circle(2, color='black')

    if i == increase_speed:
        t.speed(-1)

t.screen.exitonclick()
t.screen.mainloop()