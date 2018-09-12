#!/bin/bash
if [ "$#" -eq 1 ]; then
    make clean
    make BUILD_TYPE=debug all
    ./cluster "data/data.txt" "kmeans" "$1"
elif [ "$#" -eq 3 ]; then
    make clean
    make BUILD_TYPE=debug all
    ./cluster "data/data.txt" "$1" "$2" "$3"
else 
    echo "Illegal number of parameters ($#)"
fi
