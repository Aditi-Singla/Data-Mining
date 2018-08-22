#!/bin/bash
if [ -f fpm ]; then
    if [ "$#" == 4 ]; then
        ./fpm "$1" "$2" "$3" "$4"
    elif [ "$#" == 2 ] && [ "$2" == "-plot" ]; then
        python plot.py "$1" --supports 5 10 25 50 90
    else
        echo "Illegal number of parameters ($#), should be 4"
    fi
else
    echo "Executable not found, run compile.sh first"
fi 