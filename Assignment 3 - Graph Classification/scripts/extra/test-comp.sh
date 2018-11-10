#!/bin/bash
TEST=$1
TEST_FILE=data/"$TEST".txt
TEST_FILE2=data/"$TEST"_fsg.txt

if [ -f  $TEST_FILE ]; then
    if [ ! -f  $TEST_FILE2 ]; then
        sed -e 's/e/u/g' $TEST_FILE > $TEST_FILE2
    fi
    python scripts/plot.py $TEST_FILE --supports 5 10 25 50 95
else
    echo "Can't find data/"$1".txt"
fi 
