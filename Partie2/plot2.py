import matplotlib.pyplot as plt 
import pandas as pd
import numpy as np

data1 = pd.read_csv("perf_test_and_set.csv", sep=";")
data2 = pd.read_csv("perf_test_and_test_and_set.csv", sep=";")

def graph(d, title, xlab, ylab):
    plt.title(title)
    plt.boxplot(d, showmeans=True)
    plt.xlabel(xlab)
    plt.ylabel(ylab)
    plt.show()

n=len(data1[" Time elapsed [s]"]) // 5
arr1 = np.zeros((n,5))
arr2 = np.zeros((n,5))
for i in range(n):
    for j in range(5):
        arr1[i][j] = data1[" Time elapsed [s]"][i*5 + j]
        arr2[i][j] = data2[" Time elapsed [s]"][i*5 + j]

graph(arr1.transpose(), "Graph de performance test and set ", "Number of threads", 'Time elapsed [s]')
graph(arr2.transpose(), "Graph de performance test and test and set ", "Number of threads", 'Time elapsed [s]')