#!/bin/bash
if [ "$#" -ne 4 ]; then
    echo "Illegal number of parameters ($#), should be 4"
else
    make clean
    make all
    ./fpm "$1" "$2" "$3" "$4"
fi
