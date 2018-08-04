#!/bin/bash
if [ "$#" -eq 1 ]; then
    make clean
    make all
    ./fpm "data/retail.dat" "$1" "-apriori" "output"
elif [ "$#" -eq 2 ]; then
    make clean
    make all
    ./fpm "data/retail.dat" "$1" "$2" "output"
else 
    echo "Illegal number of parameters ($#)"
fi
