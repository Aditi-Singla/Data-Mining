#include "fpTree.h"

#include <algorithm>
#include <cmath>

using namespace std;

/*
    FP Node
*/
fpNode::fpNode() {};
fpNode::fpNode(int i, int c) : item(i), count(c) {};
fpNode::fpNode(int i, fpNode* p) : item(i), parent(p) {};
fpNode::fpNode(int i, int c, fpNode* p) : item(i), count(c), parent(p) {}; 

/*
    FP Tree
*/
fpTree::fpTree(string &inFileName) {
    inFile = inFileName;
}

void fpTree::firstPass(double suppThold) {
    numTransactions = 0;

    // first pass over db - get frequencies of items
    ifstream inputStream(inFile);
    if (inputStream.is_open()) {
        string line;
        while (getline(inputStream, line)) {
            set<int> transaction = parseLine(line);
            for (auto it = transaction.begin(); it != transaction.end(); it++) {
                priorityMap[*it] += 1;
            }
            numTransactions += 1;
        }
        inputStream.close();
    }

    // calculate frequent items and keep in priority map
    for (auto it = priorityMap.begin(); it != priorityMap.end();) {
        if ((it->second * 100.0) / numTransactions < suppThold) {
            it = priorityMap.erase(it);
        }
        else {
            it++;
        }
    }
}

void fpTree::buildFPTree() {
    
}

vector<item_set> fpTree::getFrequentItemsets(double suppThold) {

    // run the first pass - initialise priority map
    firstPass(suppThold);

    // build the FP Tree
    buildFPTree();

    return freqItemsets;
}