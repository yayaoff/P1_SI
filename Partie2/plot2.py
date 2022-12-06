import matplotlib.pyplot as plt 
import pandas as pd
import numpy as np

data = pd.read_csv("p.csv", sep=";")

def graph(d, title, xlab, ylab):
    plt.title(title)
    plt.boxplot(d, showmeans=True)
    plt.xlabel(xlab)
    plt.ylabel(ylab)
    plt.show()

n=len(data[" Time elapsed [s]"]) // 5
arr = np.zeros((n,5))
for i in range(n):
    for j in range(5):
        arr[i][j] = data[" Time elapsed [s]"][i*5 + j]

print(arr)
graph(arr.transpose(), "Graph de performance assembleur inline ", "Number of threads", 'Time elapsed [s]')