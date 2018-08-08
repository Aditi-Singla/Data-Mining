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
            // TODO - vector -> set?
            vector<int> transaction = parseLine(line);
            for (int item : transaction) {
                C_k[item_set{item}] += 1;
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

    map<item_set, int> C_k_1;
    // generate C_k+1 from F_k
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
            for (item_set subset : genSubsets(c)) {
                if (F_k.find(subset) == F_k.end()) {
                    allIn = false;
                    break;
                }
            }
            if (allIn) {
                C_k_1[c] = 0;
            }
        }
    }
    C_k = C_k_1;
}


vector<item_set> apriori::getFrequentItemsets(double suppThold) {
    // run the first pass - initialise F_1
    firstPass(suppThold);

    while (!F_k.empty()) {
        generateCandidates();
        k += 1;
        set<item_set> F_k_1;
        // calculate the support
        ifstream inputStream(inFile);
        if (inputStream.is_open()) {
            string line;
            while (getline(inputStream, line)) {
                // TODO - vector -> set?
                vector<int> transaction = parseLine(line);
                for (item_set c : C_k) {
                    // TODO - subset query
                    if (C_k[c] < rawSuppThold && c in transaction) {
                        C_k[c] += 1;
                    }
                }

            }
            inputStream.close();
        }

        // calculate the frequent items and prune
        for (auto it = C_k.begin(); it != C_k.end(); it++) {
            if (it->second >= rawSuppThold) {
                F_k_1.insert(it->first);
            }
        }
        F_k = F_k_1;
    }

    cout << numTransactions << ' ' << F_k.size() << endl;

    return freqItemsets;
}