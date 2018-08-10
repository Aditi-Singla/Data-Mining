#!/bin/bash
if [ "$#" -eq 1 ]; then
    make clean
    make BUILD_TYPE=test all
    ./fpm "data/retail.dat" "$1" "-apriori" "output-apriori"
elif [ "$#" -eq 2 ]; then
    make clean
    make BUILD_TYPE=test all
    ./fpm "data/retail.dat" "$1" "$2" "output$2"
else 
    echo "Illegal number of parameters ($#)"
fi
