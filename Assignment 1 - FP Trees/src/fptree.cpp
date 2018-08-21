#include "fpTree.h"

#include <algorithm>
#include <cmath>

using namespace std;

/*
    FP Node
*/
fpNode::fpNode() : parent(NULL), next(NULL) {};
fpNode::fpNode(item i, int c) : Item(i), count(c), parent(NULL), next(NULL) {};
fpNode::fpNode(item i, fpNode* p) : Item(i), parent(p), next(NULL) {};
fpNode::fpNode(item i, int c, fpNode* p) : Item(i), count(c), parent(p), next(NULL) {};

vector<item> fpNode::getTransaction() {
    
    vector<item> transaction;
    fpNode* curr = this;   
    while (curr->parent->parent != NULL) {
        curr = curr->parent;
        transaction.push_back(curr->Item);
    }
    // TODO - better way to handle this?
    reverse(transaction.begin(), transaction.end());
    return transaction;
}

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
    FILE* inputStream = fopen(inFile.c_str(), "r");
    vector<item> transaction;
    while (parseLineVec(inputStream, transaction)) {
        for (auto it = transaction.begin(); it != transaction.end(); it++) {
            priorityMap[*it] += 1;
        }
        numTransactions += 1;
        transaction.clear();
    }
    fclose(inputStream);

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

void fpTree::addTransaction(vector<item> &transaction, int count, bool priorityCheck) {

    fpNode* par = root;
    // build tree per transaction
    for (auto& item : transaction) {
        // if priorityCheck is false, add all items else check if item is frequent
        if (!priorityCheck || (priorityMap.find(item) != priorityMap.end())) {
            fpNode* curr;
            auto it = par->children.find(item);

            if (it == par->children.end()) {
                // new prefix - new node
                curr = new fpNode(item, count, par);
                par->children[item] = curr;
                auto it1 = headPointers.find(item);
                if (it1 == headPointers.end()) {
                    headPointers[item] = new fpNode(item,count);
                    currPointers[item] = headPointers[item];
                }
                else {
                    headPointers[item]->count += count;
                }
                // update current pointers
                currPointers[item]->next = curr;
                currPointers[item] = curr;
            } 
            else {
                // prefix already in the tree
                curr = it->second;
                curr->count += count;
                headPointers[item]->count += count;
            }
            par = curr;
        }
        else {
            // all infrequent items - ignore afterwards
            break;
        }
    }
}

void fpTree::buildFPTree() {
    // initialise root
    root = new fpNode;

    FILE* inputStream = fopen(inFile.c_str(), "r");
    vector<item> transaction;
    while (parseLineVec(inputStream, transaction)) {
        // sort according to frequency
        sort(transaction.begin(), transaction.end(), sortByFrequency(this));
        
        addTransaction(transaction, 1, true);
        transaction.clear();
    }
    fclose(inputStream);

}

bool fpTree::singlePrefixPath() {
    fpNode* curr = root;
    while (!curr->children.empty()) {
        if (curr->children.size() > 1)
            return false;
        curr = curr->children.begin()->second;
    }
    return true;
}

vector<item_set> getPowerSet(item_set &itemset) {
    vector<item_set> powerset;    
    if (itemset.size() == 1) {
        powerset.push_back(itemset);
    }

    if (itemset.size() > 1) {
        item Item  = itemset[0];
        item_set tempset;
        tempset.push_back(Item);
        powerset.push_back(tempset);
        item_set sub(itemset.begin()+1,itemset.end());
        vector<item_set> powerset1 = getPowerSet(sub);
        
        for (auto itemset1 : powerset1) {
            powerset.push_back(itemset1);
            itemset1.push_back(Item);
            sort(itemset1.begin(),itemset1.end());
            powerset.push_back(itemset1);
        }        
    }    
    return powerset; 
}

void printTree (fpNode* node) {
    cout << node->Item << " -> " << node->count << endl;
    for (auto it = node->children.begin(); it != node->children.end(); it++){
        cout << node->Item << " : ";
        printTree(it->second);
    }
}

void fpTree::printHeadPointers() {
    cout << "headPointers : " << endl;
    for (auto it = headPointers.begin(); it != headPointers.end(); it++){
        cout << it->first << " : " << it->second->count << endl;
    }
    cout << "Done" << endl;
}

void fpTree::fpGrowth() {

    if (root->children.empty()) {
        return;
    }
    if (singlePrefixPath()) {
        /* Make all possible subsets and return them, since
         the infrequent items were pruned while construction of fpTree
        */
        item_set transaction;
        fpNode* curr = root;
        // Root has a child, children not empty
        while (!curr->children.empty()) {
            curr = curr->children.begin()->second;
            if (curr->count < rawSuppThold)
                break;
            transaction.push_back(curr->Item);
        }
        freqItemsets = getPowerSet(transaction);
    }
    else {
        // Multi Prefix Path, traverse over the pointer table and go on one by one
        for (auto it = headPointers.begin(); it != headPointers.end(); it++) {
            item Item = it->first;
            fpNode* node = it->second;
            if (node->count < rawSuppThold) {
                continue;
            }
            freqItemsets.push_back(item_set{Item});
            fpTree* subTree = new fpTree(rawSuppThold);
            subTree->root = new fpNode;
            while (node->next != NULL) {
                node = node->next;
                int count = node->count;
                // Get all the items from root to this item (excluding this item)
                vector<item> transaction = node->getTransaction();
                subTree->addTransaction(transaction, node->count, false);
            }
            subTree->fpGrowth();
            vector<item_set> freqItemsetsSubtree = subTree->getFrequentItemsets();
            for (auto& itemset : freqItemsetsSubtree) {
                itemset.push_back(Item);
                sort(itemset.begin(), itemset.end());
            }
            freqItemsets.insert(freqItemsets.end(), freqItemsetsSubtree.begin(), freqItemsetsSubtree.end());
        }
    }
} 

vector<item_set> fpTree::getFrequentItemsets() {
    return freqItemsets;
}


vector<item_set> fpTree::getFrequentItemsets(double suppThold) {
    // run the first pass - initialise priority map
    firstPass(suppThold);

    // build the FP Tree
    buildFPTree();

    // run the fp tree growth
    fpGrowth();

    return freqItemsets;
}
