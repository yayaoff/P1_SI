#!/usr/bin/bash


touch f.txt
touch p.csv
echo "Number of threads; Measure; Time elapsed [s]" >> p.csv
gcc verrou.c -o verrou.out
for i in $(seq 1 1 $1)
do
    for j in 1 2 3 4 5
        do
        A=$((6400/$i))
        $(/usr/bin/time -f %e -o f.txt ./verrou.out $A)
        echo "$i;$j;$(cat f.txt) " &>> p.csv
        done
done
rm *.out
rm f.txt