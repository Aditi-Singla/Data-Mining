#!/bin/bash
if [ "$#" -eq 3 ]; then
    make clean
    make BUILD_TYPE=debug all
    ./cluster "$3" "$1" "$2"
elif [ "$#" -eq 3 ]; then
    make clean
    make BUILD_TYPE=debug all
    ./cluster "$4" "$1" "$2" "$3"
else 
    echo "Illegal number of parameters ($#)"
fi
