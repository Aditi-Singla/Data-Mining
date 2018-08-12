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

fpTree::fpTree(int rawSupportThreshold) {
    rawSuppThold = rawSupportThreshold;
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

    // keep the raw support threshold - used in later passes
    rawSuppThold = ceil((suppThold / 100.0) * numTransactions);
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
    // for (auto it = priorityMap.begin(); it != priorityMap.end(); it++) {
    //     headPointers[it->first] = new fpNode();
    //     currPointers[it->first] = headPointers[it->first];
    // }
}

void fpTree::addTransaction(vector<int> transaction, int count, bool priorityCheck) {

    fpNode* par = root;
    // build tree per transaction
    for (int item : transaction) {
        // if priorityCheck is false, add all items
        // else check if item is frequent
        if (!priorityCheck || (priorityMap.find(item) != priorityMap.end())) {
            fpNode* curr;
            auto it = par->children.find(item);
            // cout << "Here" << endl;
            // for (auto it1 = par->children.begin(); it1 != par->children.end(); it1++) {
            //     cout << it1->first << " ";
            // }
            // cout << endl;
            if (it == par->children.end()) {
                // cout << "Hello" << endl;
                // new prefix - new node
                curr = new fpNode(item, count, par);
                par->children[item] = curr;
                auto it1 = headPointers.find(item);
                if (it1 == headPointers.end()) {
                    headPointers[item] = new fpNode(item,count);
                    currPointers[item] = headPointers[item];
                }
                else {
                    headPointers[item]->count++;
                }
                // update current pointers
                currPointers[item]->next = curr;
                currPointers[item] = curr;
            } 
            else {
                // cout << "Hi" << endl;
                // prefix already in the tree
                curr = it->second;
                curr->count += count;
                headPointers[item]->count += count;
            }
            par = curr;
        }
        else {
            // cout << "There" << endl;
            // all infrequent items - ignore afterwards
            break;
        }
    }
}


void fpTree::buildFPTree() {

    // initialise root, head and current pointers for each frequent item
    initialiseTree();

    ifstream inputStream(inFile);
    if (inputStream.is_open()) {

        string line;
        while (getline(inputStream, line)) {
            vector<int> transaction = parseLineVec(line);
            // sort according to frequency
            sort(transaction.begin(), transaction.end(), sortByFrequency(this));

            addTransaction(transaction, 1, true);
            
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