#!/bin/bash
if [ "$#" -eq 1 ]; then
    make clean
    make BUILD_TYPE=test all
    valgrind --tool=callgrind /cluster "data/data.txt" "kmeans" "$1"
    kcachegrind&
elif [ "$#" -eq 3 ]; then
    make clean
    make BUILD_TYPE=test all
    valgrind --tool=callgrind ./cluster "data/data.txt" "$1" "$2" "$3"
    kcachegrind&
else 
    echo "Illegal number of parameters ($#)"
fi