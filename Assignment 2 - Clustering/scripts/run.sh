#!/bin/bash
if [ -f cluster ]; then
    if [ "$#" == 3 ] && [ "$2" == "-kmeans" ]; then
        ./cluster "$1" "kmeans" "$3"
    elif [ "$#" == 4 ] && [ "$2" == "-dbscan" ]; then
        ./cluster "$1" "dbscan" "$3" "$4"
    elif [ "$#" == 4 ] && [ "$2" == "-optics" ]; then
        ./cluster "$1" "optics" "$3" "$4"
    else
        echo "Illegal number of parameters ($#)"
    fi
else
    echo "Executable not found, run compile.sh first"
fi 