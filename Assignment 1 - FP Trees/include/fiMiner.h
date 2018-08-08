#ifndef FIMINER_H
#define FIMINER_H

#include <set>
#include <algorithm>

#include "Input.h"

typedef std::vector<int> item_set;

class fiMiner {

    public :
        std::string inFile;
        int numTransactions;    // total num of transactions in db
        std::vector<item_set> freqItemsets;

        fiMiner() {}
        virtual std::vector<item_set> getFrequentItemsets(double suppThold) = 0;
};

#endif