#!/usr/bin/bash

touch csv/perf_philo.csv
touch csv/perf_prod_cons.csv
touch csv/perf_wr_read.csv
touch f.txt
echo "Number of threads; Number of execution; Time elapsed [s]" >> csv/perf_philo.csv
echo "Number of threads; Number of execution; Time elapsed [s]" >> csv/perf_prod_cons.csv
echo "Number of threads; Number of execution; Time elapsed [s]" >> csv/perf_wr_read.csv
make fec_philo
make fec_wr_read
make fec_prod_cons
for i in 1 2 4 8 16 32 64
do
    for j in 1 2 3 4 5
    do
    
    $(/usr/bin/time -f %e -o f.txt ./fec_philo.out $i)
    echo "$i; $j; $(cat f.txt) " &>> csv/perf_philo.csv
    
    $(/usr/bin/time -f %e -o f.txt ./fec_wr_read.out $i $i)
    echo "$i; $j; $(cat f.txt) " &>> csv/perf_wr_read.csv

    $(/usr/bin/time -f %e -o f.txt ./fec_prod_cons.out $i $i)
    echo "$i; $j; $(cat f.txt) " &>> csv/perf_prod_cons.csv
    done
done

rm -f *.out
rm -f f.txt