#ifndef APRIORI_H
#define APRIORI_H

#include "fiMiner.h"

class apriori : public fiMiner {

    public:
        apriori(std::string &inFileName);
        std::vector<item_set> getFrequentItemsets(double suppThold);
};

#endif