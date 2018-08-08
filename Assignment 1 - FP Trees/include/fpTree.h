#ifndef FPTREE_H
#define FPTREE_H

#include "fiMiner.h"

class fpTree : public fiMiner {

    public:
        fpTree(std::string &inFileName);
        std::vector<item_set> getFrequentItemsets(double suppThold);
};

#endif