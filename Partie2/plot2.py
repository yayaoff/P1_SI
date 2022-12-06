import matplotlib.pyplot as plt 
import pandas as pd
import numpy as np

data1 = pd.read_csv("perf_test_and_set.csv", sep=";")
data2 = pd.read_csv("perf_test_and_test_and_set.csv", sep=";")
t=[1, 2, 4, 8, 16, 32, 64]

def graph(d, title, xlab, ylab):
    plt.title(title)
    plt.boxplot(d, showmeans=True)
    plt.xlabel(xlab)
    plt.ylabel(ylab)
    plt.xticks([1,2,3,4,5,6,7],t)
    ttl=title+'.png'
    plt.savefig(ttl)
    plt.close()

n=len(data1[" Time elapsed [s]"]) // 5
arr1 = np.zeros((n,5))
arr2 = np.zeros((n,5))
for i in range(n): 
    for j in range(5):
        arr1[i][j] = data1[" Time elapsed [s]"][i*5 + j]
        arr2[i][j] = data2[" Time elapsed [s]"][i*5 + j]

graph(arr1.transpose(), "Graph de performance test and set ", "Number of threads", 'Time elapsed [s]')
graph(arr2.transpose(), "Graph de performance test and test and set ", "Number of threads", 'Time elapsed [s]')