#!/bin/bash
rm data/*.txt data/*.fp
unzip data/cancer.zip -d data/.
python scripts/extra/createTest1.py data/data.txt --active data/actives.txt
if [ "$#" == 1 ]; then
    ./scripts/run.sh data/data_train.txt data/data_train_active.txt data/data_train_inactive.txt data/data_test.txt "$1"
else
    ./scripts/run.sh data/data_train.txt data/data_train_active.txt data/data_train_inactive.txt data/data_test.txt
fi
rm data/*.txt data/*.fp