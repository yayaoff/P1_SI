import matplotlib.pyplot as plt 
import pandas as pd
import numpy as np

t=[1, 2, 4, 8, 16, 32, 64]
n=len(t)
data1=pd.read_csv("csv/perf_philo.csv", sep=';')
data2=pd.read_csv("csv/perf_wr_read.csv", sep=';')
data3=pd.read_csv("csv/perf_prod_cons.csv", sep=';')

def graph(d, title, xlab, ylab):
    plt.title(title)
    plt.boxplot(d, showmeans=True)
    plt.xlabel(xlab)
    plt.ylabel(ylab)
    plt.xticks([1,2,3,4,5,6,7],t)
    ttl='png/'+title+'.png'
    plt.savefig(ttl)
    plt.close()

arr1=np.zeros((n,5))
arr2=np.zeros((n,5))
arr3=np.zeros((n,5))

for i in range(n):
    for j in range(5):
        arr1[i][j] = data1[" Time elapsed [s]"][i*5 + j]
        arr2[i][j] = data2[" Time elapsed [s]"][i*5 + j]
        arr3[i][j] = data3[" Time elapsed [s]"][i*5 + j]


graph(arr1.transpose(),"Performance of Philosophers", "Number of threads", "Time elapsed [s]")
graph(arr2.transpose(),"Performance of writer reader", "Number of threads", "Time elapsed [s]")
graph(arr3.transpose(),"Performance of Producers Consumers", "Number of threads", "Time elapsed [s]")