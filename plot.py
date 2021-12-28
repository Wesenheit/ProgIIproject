import matplotlib.pyplot as plt
import math
from sys import argv
def get(name):
    tab=[]
    with open(name) as f:
        for line in f:
            tab=[*tab,*line.split()]
    return list(map(float,tab))
plt.hist(list(map(lambda x: 360*x/(2*math.pi), get(argv[1]))),bins=20)
plt.show()
