import matplotlib.pyplot as plt
from sys import argv
f=open(argv[1])
tab=f.readline().split()
print(tab)
plt.hist(list(map(float,tab)),bins=20)
plt.show()