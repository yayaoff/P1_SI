#!/usr/bin/bash


touch f.txt
touch p.csv
gcc verrou.c -o verrou.out
for i in $(seq 1 1 $1)
do
    A=$((6400/$i))
    $(/usr/bin/time -f %e -o f.txt ./verrou.out $A)
    echo "$i; $(cat f.txt) " &>> p.csv
done
rm *.out
rm f.txt