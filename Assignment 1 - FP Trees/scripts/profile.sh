#!/bin/bash
if [ "$#" -eq 1 ]; then
    make clean
    make BUILD_TYPE=test all
    valgrind --tool=callgrind ./fpm "data/retail.dat" "$1" "-fptree" "output-fptree"
    kcachegrind&
elif [ "$#" -eq 2 ]; then
    make clean
    make BUILD_TYPE=test all
    valgrind --tool=callgrind ./fpm "data/retail.dat" "$1" "$2" "output$2"
    kcachegrind&
else 
    echo "Illegal number of parameters ($#)"
fi
