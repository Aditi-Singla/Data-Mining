#!/bin/bash
# if [ -f graph ]; then
if [ "$#" == 4 ]; then
    python scripts/format.py "$1" --active "$2" --inactive "$3"
    python graphToVec.py "$1" "$2" "$3" "$4"
else
    echo "Illegal number of parameters ($#)"
fi
# else
#     echo "Executable not found, run compile.sh first"
# fi 