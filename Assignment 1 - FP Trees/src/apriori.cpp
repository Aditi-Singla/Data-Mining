#include "apriori.h"

#include <algorithm>

using namespace std;

apriori::apriori(string &inFileName) {
    inFile = inFileName;
}

void apriori::firstPass(double suppThold) {
    numTransactions = 0;
    
    // first pass over the db - init k as 1
    k = 1;
    ifstream inputStream(inFile);
    if (inputStream.is_open()) {
        string line;
        while (getline(inputStream, line)) {
            // TODO - fix 2 passes over each transaction, one to pass other to update count
            set<int> transaction = parseLine(line);
            for (auto it = transaction.begin(); it != transaction.end(); it++) {
                C_k[item_set{*it}] += 1;
            }
            numTransactions += 1;
        }
        inputStream.close();
    }

    // calculate the frequent items and prune
    for (auto it = C_k.begin(); it != C_k.end(); it++) {
        if (it->second * 100.0 / numTransactions >= suppThold) {
            F_k.insert(it->first);
        }
    }

    // keep the raw support threshold - used in later passes
    rawSuppThold = ceil((suppThold / 100.0) * numTransactions);
}

void apriori::generateCandidates() {
    // clear C_k and generate C_k+1 from _k
    C_k.clear();
    for (auto it1 = F_k.begin(); it1 != F_k.end(); it1++) {
        for (auto it2 = F_k.begin(); it2 != it1; it2++) {
            item_set c;
            item_set f1 = *it1, f2 = *it2;
            if (equal(f1.begin(), f1.begin() + k - 1, f2.begin())) {
                // same up to k - 1 elements - merge them
                c.assign(f1.begin(), f1.end() - 1);
                c.push_back(min(f1.back(), f2.back()));
                c.push_back(max(f1.back(), f2.back()));
            }

            // check frequent subsets
            bool allIn = true;
            // TODO - subset generation
            // for (item_set subset : genSubsets(c)) {
            //     if (F_k.find(subset) == F_k.end()) {
            //         allIn = false;
            //         break;
            //     }
            // }
            if (allIn) {
                C_k[c] = 0;
            }
        }
    }
}

vector<item_set> apriori::getFrequentItemsets(double suppThold) {
    // run the first pass - initialise F_1
    firstPass(suppThold);

    while (!F_k.empty()) {
        generateCandidates();
        k += 1;
        // calculate the support
        ifstream inputStream(inFile);
        if (inputStream.is_open()) {
            string line;
            while (getline(inputStream, line)) {
                set<int> transaction = parseLine(line);
                for (auto it = C_k.begin(); it != C_k.end(); it++) {
                    item_set c = it->first;
                    if (C_k[c] < rawSuppThold && includes(
                        transaction.begin(), transaction.end(), 
                        c.begin(), c.end())) {
                        C_k[c] += 1;
                    }
                }
            }
            inputStream.close();
        }

        // prune to get frequent items
        F_k.clear();
        for (auto it = C_k.begin(); it != C_k.end(); it++) {
            if (it->second >= rawSuppThold) {
                F_k.insert(it->first);
            }
        }
    }
    return freqItemsets;
}