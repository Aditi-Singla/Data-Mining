#!/bin/bash
if [ "$#" -eq 3 ]; then
    make clean
    make BUILD_TYPE=test all
    valgrind --tool=callgrind ./cluster "$3" "$1" "$2"
    kcachegrind&
elif [ "$#" -eq 4 ]; then
    make clean
    make BUILD_TYPE=test all
    valgrind --tool=callgrind ./cluster "$4" "$1" "$2" "$3"
    kcachegrind&
else 
    echo "Illegal number of parameters ($#)"
fi