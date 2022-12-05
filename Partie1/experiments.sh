#!/usr/bin/bash

touch perf_philo.csv
touch perf_prod_cons.csv
touch perf_wr_read.csv
touch f.txt
echo "Number of threads; Number of execution; Time elapsed [s]" >> perf_philo.csv
echo "Number of threads; Number of execution; Time elapsed [s]" >> perf_prod_cons.csv
echo "Number of threads; Number of execution; Time elapsed [s]" >> perf_wr_read.csv
for i in 1 2 4 8 16 32 64
do
    for j in 1 2 3 4 5
    do
    make fec_philo
    $(/usr/bin/time -f %e -o f.txt ./fec_philo $i)
    echo "$i; $j; $(cat f.txt) " &>> perf_philo.csv
    rm fec_philo

    make fec_wr_read
    $(/usr/bin/time -f %e -o f.txt ./fec_wr_read $i $i)
    echo "$i; $j; $(cat f.txt) " &>> perf_wr_read.csv
    rm fec_wr_read

    make fec_prod_cons
    $(/usr/bin/time -f %e -o f.txt ./fec_prod_cons $i $i)
    echo "$i; $j; $(cat f.txt) " &>> perf_prod_cons.csv
    rm fec_prod_cons

    done
done

rm f.txt