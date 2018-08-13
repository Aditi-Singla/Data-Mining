#!/bin/bash
if [ "$#" -eq 1 ]; then
    make clean
    make BUILD_TYPE=test all
    ./fpm "data/retail.dat" "$1" "-apriori" "output-apriori"
    python check.py "data/retail.dat" "output-apriori.txt" "$1"
elif [ "$#" -eq 2 ]; then
    make clean
    make BUILD_TYPE=test all
    ./fpm "data/retail.dat" "$1" "$2" "output$2"
    python check.py "data/retail.dat" "output$2.txt" "$1"
else 
    echo "Illegal number of parameters ($#)"
fi
