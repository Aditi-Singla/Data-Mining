#!/bin/bash
if [ "$#" == 4 ]; then
    python scripts/format.py "$1" --active "$2" --inactive "$3"
    python scripts/format.py "$4"
    python graphToVec.py "$1" "$4"
else
    echo "Illegal number of parameters ($#)"
fi