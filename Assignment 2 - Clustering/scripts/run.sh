#!/bin/bash
if [ -f cluster ]; then
    if [ "$#" == 3 ] && [ "$1" == "-kmeans" ]; then
        ./cluster "$3" "$1" "$2"
    elif [ "$#" == 4 ]; then
        ./cluster "$4" "$1" "$2" "$3"
        if [ "$1" == "-optics" ]; then
            python2 plot.py --input "$4" --reachability optics.txt
        fi
    else
        echo "Illegal number of parameters ($#)"
    fi
else
    echo "Executable not found, run compile.sh first"
fi 