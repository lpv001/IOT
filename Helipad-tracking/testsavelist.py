


import pickle
import time
x = []
y=[]
score = 0
data = 0
while True:
    score += 1
    data +=2
    x.append(score)
    y.append(data)
    with open("file.txt", 'wb') as fp:
        pickle.dump(x, fp)
    with open("file1.txt", 'wb') as fp:
        pickle.dump(y, fp)

    if score >10:
        break