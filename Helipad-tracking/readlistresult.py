import pickle
import numpy as np
import matplotlib.pyplot as plt

with open("data.txt", 'rb') as fp:
    errorx = pickle.load(fp)
with open("data1.txt", 'rb') as fp:
    errory = pickle.load(fp)

print(len(errorx))

t = np.linspace(0,248,248)
print(len(t))
plt.grid(True)
#plt.xlabel('x')
plt.ylabel('Error (px)')
plt.title('Tracking Test')
plt.plot(t,errorx, 'b', label='Error_x (pan)')
plt.plot(t,errory, 'r', label='Error_y (tilt)')
plt.legend(loc='upper right')
plt.show()