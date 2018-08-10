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
            vector<int> transaction = parseLineVec(line);
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

struct fpTree::sortByFrequency {
    fpTree* parent;    // TODO - look into this
    sortByFrequency(fpTree* p) : parent(p) {};
    bool operator()(int const &a, int const &b) const {
        int p_a = -1, p_b = -1;
        // On checking priorityMap[a] vs [b], if either does not exist in it,
        // new key added and value set to zero - thus this comparision
        if (parent->priorityMap.find(a) != parent->priorityMap.end()) {
            p_a = parent->priorityMap[a];
        }
        if (parent->priorityMap.find(b) != parent->priorityMap.end()) {
            p_b = parent->priorityMap[b];
        }
        return p_a > p_b; 
    }
};

void fpTree::initialiseTree() {
    root = new fpNode;
    for (auto it = priorityMap.begin(); it != priorityMap.end(); it++) {
        headPointers[it->first] = new fpNode();
        currPointers[it->first] = headPointers[it->first];
    }
}


void fpTree::buildFPTree() {

    // initialise root, head and current pointers for each frequent item
    initialiseTree();

    ifstream inputStream(inFile);
    if (inputStream.is_open()) {
        fpNode* par = root;

        string line;
        while (getline(inputStream, line)) {
            vector<int> transaction = parseLineVec(line);
            // sort according to frequency
            sort(transaction.begin(), transaction.end(), sortByFrequency(this));

            // build tree per transaction
            for (int item : transaction) {
                // check if item is frequent
                if (priorityMap.find(item) != priorityMap.end()) {
                    fpNode* curr;
                    auto it = par->children.find(curr);
                    if (it == par->children.end()) {
                        // new prefix - new node
                        curr = new fpNode(item, 1, par);
                        par->children.insert(curr);
                        // update current pointers
                        currPointers[item]->next = curr;
                        currPointers[item] = curr;
                    } 
                    else {
                        // prefix already in the tree
                        curr = *it;
                        curr->count++;
                    }
                    par = curr;
                }
                else {
                    // all infrequent items - ignore afterwards
                    break;
                }
            }
        }
        inputStream.close();
    }
}

vector<item_set> fpTree::getFrequentItemsets(double suppThold) {

    // run the first pass - initialise priority map
    firstPass(suppThold);

    // build the FP Tree
    buildFPTree();

    // run the fp tree growth
    

    return freqItemsets;
}