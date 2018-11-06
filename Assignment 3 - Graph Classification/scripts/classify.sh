#!/bin/bash
if [ -f graph ]; then
    if [ "$#" == 3 ]; then
        ./graph "$1"
    else
        echo "Illegal number of parameters ($#)"
    fi
else
    echo "Executable not found, run compile.sh first"
fi 