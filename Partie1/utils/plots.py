import matplotlib.pyplot as plt 
import pandas as pd
import numpy as np

t=[1, 2, 4, 8, 16, 32, 64]
n=len(t)
data1=pd.read_csv("../csv/perf_philo.csv", sep=';')
data2=pd.read_csv("../csv/perf_wr_read.csv", sep=';')
data3=pd.read_csv("../csv/perf_prod_cons.csv", sep=';')

def graph(d, title, xlab, ylab, mean):
    plt.title(title)
    plt.boxplot(d)
    plt.xlabel(xlab)
    plt.ylabel(ylab)
    y = np.arange(1,8,1)
    plt.xticks([1,2,3,4,5,6,7],t)
    plt.scatter(y, mean, label='Mean')
    plt.plot()
    ttl=title+'.png'
    plt.savefig(ttl)
    plt.close()

arr1=np.zeros((n,5))
arr2=np.zeros((n,5))
arr3=np.zeros((n,5))
mean1 = np.zeros(n)
mean2 = np.zeros(n)
mean3 = np.zeros(n)

j = 0
i = 0
while(i < n):
    while (j < 5):
        arr1[i][j] = data1[" Time elapsed [s]"][i*5 + j]
        arr2[i][j] = data2[" Time elapsed [s]"][i*5 + j]
        arr3[i][j] = data3[" Time elapsed [s]"][i*5 + j]
        mean1[i] += arr1[i][j] 
        mean2[i] += arr2[i][j] 
        mean3[i] += arr3[i][j] 
        j += 1
    mean1[i] /= 5
    mean2[i] /= 5
    mean3[i] /= 5
    i += 1
    j = 0

graph(arr1.transpose(),"Performance of Philosophers", "Number of threads", "Time elapsed [s]", mean1)
graph(arr2.transpose(),"Performance of writer reader", "Number of threads", "Time elapsed [s]", mean2)
graph(arr3.transpose(),"Performance of Producers Consumers", "Number of threads", "Time elapsed [s]", mean3)