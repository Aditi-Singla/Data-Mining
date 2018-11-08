#!/bin/bash
function runKMeans () {
    ./cluster data/100000-"$1"-0.txt -kmeans "$1"
    python plot.py --input data/100000-"$1"-0.txt --clusters kmeans.txt
}

function runDbscan_Optics () {
    ./cluster data/100000-"$2"-0.txt -"$1" -"$3" "$4" 
    python plot.py --input data/100000-"$2"-0.txt --clusters "$1".txt
}

make clean
make
if [ "$#" == 2 ] && [ "$1" == "kmeans" ]; then 
    if [ -f data/100000-"$2"-0.txt ]; then
        runKMeans "$2";
    else
        echo "Run python generateData.py 100000 $2 1 first"
    fi
elif [ "$#" == 4 ]; then
    if [ -f data/100000-"$2"-0.txt ]; then
        runDbscan_Optics "$1" "$2" "$3" "$4"
    else
        echo "Run python generateData.py 100000 $2 1 first"
    fi
else
    echo "Illegal number of parameters ($#)"
fi