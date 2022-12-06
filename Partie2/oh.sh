#!/usr/bin/bash

touch p_philo.csv
touch f.txt
echo "Number of threads; Number of execution; Time elapsed [s]" >> p_philo.csv
gcc our_philo.c -o p.o
for i in 1 2 4 8 16 32 64
do
    for j in 1 2 3 4 5
    do
    $(/usr/bin/time -f %e -o f.txt ./p.o $i)
    echo "$i; $j; $(cat f.txt) " &>> p_philo.csv
    done
done

rm -f *.o
rm -f f.txt