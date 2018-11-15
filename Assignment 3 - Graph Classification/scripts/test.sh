#!/bin/bash
rm data/*.txt data/*.fp
unzip data/dataset.zip -d data/.
python scripts/extra/createTest.py data/aido99_all.txt --active data/ca.txt --inactive data/ci_balanced.txt
if [ "$#" == 1 ]; then
    ./scripts/run.sh data/aido99_all_train.txt data/aido99_all_train_active.txt data/aido99_all_train_inactive.txt data/aido99_all_test.txt "$1"
else
    ./scripts/run.sh data/aido99_all_train.txt data/aido99_all_train_active.txt data/aido99_all_train_inactive.txt data/aido99_all_test.txt
fi
# rm data/*.txt data/*.fp