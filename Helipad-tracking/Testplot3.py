import matplotlib.pyplot as plt
import numpy as np
from drawnow import *
import time
import cv2

panx_e = []
tilty_e = []

plt.ion() #interactive mode to plot live data

def makeFig(): #For plotting a live graph

    plt.grid(True)
    plt.xlabel('time')
    plt.ylabel('Error')
    plt.title('Error vs time of live tracking')
    plt.plot(panx_e, label='Error_x')
    plt.legend(loc='upper right')
    plt.plot(tilty_e, label='Error_y')
    plt.legend(loc='upper right')

while True:
    errorPan=1
    errorTilt=1.1
    panx_e.append(errorPan)
    tilty_e.append(errorTilt)
    drawnow(makeFig)