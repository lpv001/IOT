import pickle



with open("file.txt", 'rb') as fp:
    b = pickle.load(fp)
with open("file1.txt", 'rb') as fp:
    c = pickle.load(fp)
print(b)
print(c)