#ifndef APRIORI_H
#define APRIORI_H

#include <map>

#include "fiMiner.h"

class apriori : public fiMiner {

    public:
        apriori(std::string &inFileName);
        std::vector<item_set> getFrequentItemsets(double suppThold);

    private:
        int k, rawSuppThold;
        std::map<item_set, int> C_k;
        std::set<item_set> F_k;
        void firstPass(double suppThold);
        void generateCandidates();
};

#endif