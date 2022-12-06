import matplotlib.pyplot as plt 
import pandas as pd
import numpy as np

t=[1, 2, 4, 8, 16, 32, 64]
n=len(t)
data=pd.read_csv("p_philo.csv", sep=';')

def graph(d, title, xlab, ylab):
    plt.title(title)
    plt.boxplot(d, showmeans=True)
    plt.xlabel(xlab)
    plt.ylabel(ylab)
    plt.xticks([1,2,3,4,5,6,7],t)
    ttl=title+'.png'
    plt.savefig(ttl)
    plt.close()

arr=np.zeros((n,5))

for i in range(n):
    for j in range(5):
        arr[i][j] = data[" Time elapsed [s]"][i*5 + j]

graph(arr.transpose(),"Performance of Philo", "Number of threads", "Time elapsed [s]")