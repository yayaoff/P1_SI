#!/usr/bin/bash

touch f.txt
touch perf_test_and_set.csv
touch perf_test_and_test_and_set.csv
echo "Number of threads; Measure; Time elapsed [s]" >> perf_test_and_set.csv
echo "Number of threads; Measure; Time elapsed [s]" >> perf_test_and_test_and_set.csv
gcc test_and_set.c -o verrou.out
gcc test_and_test_and_set.c -o verrou1.out

for i in $(seq 1 $1)
do
    for j in 1 2 3 4 5
        do
        $(/usr/bin/time -f %e -o f.txt ./verrou.out $i)
        echo "$i;$j;$(cat f.txt) " &>> perf_test_and_set.csv

        $(/usr/bin/time -f %e -o f.txt ./verrou1.out $i)
        echo "$i;$j;$(cat f.txt) " &>> perf_test_and_test_and_set.csv
        done
done
rm -f *.out
rm -f f.txt