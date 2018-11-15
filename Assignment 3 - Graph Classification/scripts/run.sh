#!/bin/bash
if [ "$#" == 4 ] || [ "$#" == 5 ]; then
	
    TRAIN_FILE_NAME="${1%.*}"
    TRAIN_FILE_EXT="${1##*.}"
    TRAIN_FILE_CONV="$TRAIN_FILE_NAME"_converted."$TRAIN_FILE_EXT"
    TRAIN_FILE_LAB="$TRAIN_FILE_NAME"_labels."$TRAIN_FILE_EXT"
    TEST_FILE_NAME="${4%.*}"
    TEST_FILE_EXT="${4##*.}"
    TEST_FILE_CONV="$TEST_FILE_NAME"_converted."$TEST_FILE_EXT"
    TEST_FILE_LAB="$TEST_FILE_NAME"_labels."$TEST_FILE_EXT"

    python scripts/format.py "$1" "$TRAIN_FILE_CONV" --labels "$TRAIN_FILE_LAB" --active "$2" --inactive "$3"
    python scripts/format.py "$4" "$TEST_FILE_CONV"

    if [ "$#" == 4 ]; then
    	python graphToVec1.py "$TRAIN_FILE_CONV" "$TRAIN_FILE_LAB" "$TEST_FILE_CONV" "$TEST_FILE_LAB" 
    else
    	python graphToVec1.py "$TRAIN_FILE_CONV" "$TRAIN_FILE_LAB" "$TEST_FILE_CONV" "$TEST_FILE_LAB" --support "$5"
    fi

    ./libraries/svm-train -t 0 -h 0 train.txt model_linear.txt
    ./libraries/svm-predict test.txt model_linear.txt predicted.txt
    python scripts/extra/fscore.py "$TEST_FILE_LAB" predicted.txt
    # rm model_linear.txt
else
    echo "Illegal number of parameters ($#)"
fi