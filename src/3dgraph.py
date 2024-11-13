import numpy as np
import math
import pandas as pd
import csv
import matplotlib.pyplot as plt
from matplotlib import cm


array = np.zeros([101,150])
print(array)
header = ['x', 'y', 'z', 'force']
file_name = 'example.csv'
csvfile = open(file_name, 'w', newline='')
csv_writer = csv.writer(csvfile)
csv_writer.writerow(header)
fig, ax = plt.subplots(subplot_kw={"projection": "3d"})


def multi_valor(angulo):

    if (angulo > 360):

        return (angulo - 360)

    elif (angulo < 0):

        return (angulo + 360)

    else:

        return angulo


def RectangulareEsfericas(x,  y,  z,  x_prima=0.0,  y_prima=0.0, z_prima=0.0):
    ro = math.sqrt(pow(x - x_prima, 2) +
                   pow(y - y_prima, 2) + pow(z - z_prima, 2))
    alfa_rad = math.atan2(y - y_prima, x - x_prima)

    return {"ro": ro, "alfa_rad": alfa_rad}


def CalculoFuerza(x, y, z, x_prima=0, y_prima=0, z_prima=0, direccion=0):
    esfericas = RectangulareEsfericas(
        x, y, z, x_prima, y_prima, z_prima)
    alfa_grad = multi_valor(math.degrees(esfericas["alfa_rad"]))
    direccion = multi_valor(direccion)
    min = multi_valor(direccion - 90)
    max = multi_valor(direccion + 90)
    a = 0.5
    if (direccion > 90 and direccion < 270):

        if (alfa_grad >= min and alfa_grad <= max):

            return (a * abs(math.sin(math.radians(alfa_grad - direccion))) + esfericas["ro"] * a)

        else:

            return (a + esfericas["ro"] * a)

    else:

        if (alfa_grad >= min or alfa_grad <= max):

            return (a * abs(math.sin(math.radians(alfa_grad - direccion))) + esfericas["ro"] * a)

        else:

            return (a + esfericas["ro"] * a)


if __name__ == '__main__':

    x1 = -50
    while (x1 < 100):
        y1 = -50
        
        while (y1 < 51):
            force = CalculoFuerza(x1/100, y1/100, 0)
            force_reward = - 5 * (force* force)
            distance_reward = RectangulareEsfericas(x1/100,y1/100,0)
            distance_reward = distance_reward["ro"]
            array[y1+50][x1+50] = CalculoFuerza(x1/100, y1/100, 0)*100
            #csv_writer.writerow([x1, y1, array[x1][y1]])

            y1 = y1+1
        x1 = x1+1

    # Make data.
    X = np.arange( -0.5, 1.0, 0.01)
    Y = np.arange( -0.5, 0.51, 0.01)
    X, Y = np.meshgrid(X, Y)
    print(type(X))
    surf = ax.plot_surface(X,Y,array, cmap=cm.coolwarm,linewidth=0, antialiased=False)
    ax.xaxis.set_label_text("[mts]")
    ax.yaxis.set_label_text("[mts]")
    clb=fig.colorbar(surf, shrink=0.5, aspect=10)
    clb.ax.yaxis.set_label_text("[N]")
    plt.show()
