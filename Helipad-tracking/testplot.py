import matplotlib.pyplot as plt
import numpy

i = 0
x = list()
y = list()

plt.grid(True)
plt.xlabel('x')
plt.ylabel('y')
plt.title('Testing')
plt.axis([0,10,-1,1])

while i < 1000:
    z = numpy.random.random()
    
    x.append(i)
    y.append(z)
    plt.scatter(i,z)
    i += 1
    plt.plot(x,y,'b',linewidth=2,markersize=7,label='Blue Line')
    plt.legend(loc='upper right')
    plt.show()