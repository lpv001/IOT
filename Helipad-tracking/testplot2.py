import matplotlib.pyplot as plt
import numpy as np
from drawnow import *
import time
import cv2
x = []
y = []
z = 0
plt.ion() #interactive mode to plot live data

def makeFig():

    plt.grid(True)
    plt.xlabel('time')
    plt.ylabel('Error')
    plt.title('Error vs time of live tracking')
    plt.plot(x, label='Error_x')
    plt.legend(loc='upper right')
    plt.plot(y, label='Error_y')
    plt.legend(loc='upper right')


while True:
    time.sleep(0.1)
    z += 0.1
    x1 = np.cos(z)
    y1 = np.sin(z)
    x.append(x1)
    y.append(y1)
    drawnow(makeFig)
    plt.pause(.000001)

    