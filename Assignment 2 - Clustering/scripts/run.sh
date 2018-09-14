#!/bin/bash
if [ -f cluster ]; then
    if [ "$#" == 3 ] then
        ./cluster "$3" "$1" "$2"
    elif [ "$#" == 4 ] then
        ./cluster "$4" "$1" "$2" "$3"
    else
        echo "Illegal number of parameters ($#)"
    fi
else
    echo "Executable not found, run compile.sh first"
fi 