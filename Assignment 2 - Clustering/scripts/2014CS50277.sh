#!/bin/bash
if [ -f cluster ]; then
    if [ "$#" == 3 ] && [ "$1" == "-kmeans" ]; then
        time ./cluster "$3" "$1" "$2"
        python2 plot.py --input "$3" --clusters kmeans.txt
    elif [ "$#" == 4 ]; then
        time ./cluster "$4" "$1" "$2" "$3"
        if [ "$1" == "-dbscan" ]; then
        	python2 plot.py --input "$4" --clusters dbscan.txt
        elif [ "$1" == "-optics" ]; then
        	python2 plot.py --input "$4" --reachability optics.txt
        else
        	echo "Illegal method call"
        fi
    else
        echo "Illegal number of parameters ($#)"
    fi
else
    echo "Executable not found, run compile.sh first"
fi 