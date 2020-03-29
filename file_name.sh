#!/bin/bash

GENERATIONS=( 100  100 1000 5000 10000 30000 ) 
THREADS=(1 2 4 8 16)
NRUNS=5
MAPS=("tests/1.in" "tests/2.in" "tests/3.in" "tests/4.in" "tests/5.in" "tests/6.in" "tests/7.in" "tests/8.in" "tests/9.in" "tests/10.in" "tests/11.in" "tests/12.in") 

for IT in "${GENERATIONS[@]}"; do
    for TH in "${THREADS[@]}"; do
        for M in "${MAPS[@]}"; do
            for R in $NRUNS; do
                ./glife -t $TH $IT $M
            done
        done
    done
done | tee output_file.csv