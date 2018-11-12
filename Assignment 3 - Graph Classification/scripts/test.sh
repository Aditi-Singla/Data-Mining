#!/bin/bash
run(){
	./libraries/svm-train -t 0 -c 500 train.txt model_linear.txt
	./libraries/svm-predict test.txt model_linear.txt predicted.txt
	python scripts/fscore.py "$1" predicted.txt
	rm model_linear.txt predicted.txt
}

if [ "$#" == 3 ]; then
    python graphToVec.py "$1" "$2" --support "$3"
    run "$2"
elif [ "$#" == 2 ]; then
    python graphToVec.py "$1" "$2"
    run "$2"
else
    echo "Illegal number of parameters ($#)"
fi