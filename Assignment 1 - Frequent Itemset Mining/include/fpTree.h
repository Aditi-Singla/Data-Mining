#ifndef FPTREE_H
#define FPTREE_H

#include <set>
#include <unordered_set>

#include "fiMiner.h"

class fpNode {
    public:
        item Item;
        int count;      
        fpNode* next;                              // next item in the linked list
        fpNode* parent;
        std::unordered_map<int, fpNode*> children; // item to fpNode*
        fpNode();
        fpNode(item i, int c);
        fpNode(item i, fpNode* p);
        fpNode(item i, int c, fpNode* p);
        std::vector<int> getTransaction();
};

class fpTree : public fiMiner {

    public:
        fpNode* root;
        fpTree(std::string &inFileName);
        fpTree(int rawSupportThreshold);
        std::vector<item_set> getFrequentItemsets();
        std::vector<item_set> getFrequentItemsets(double suppThold);
        
    private:
        int numTransactions, rawSuppThold;
        std::unordered_map<item, fpNode*> headPointers;
        std::unordered_map<item, fpNode*> currPointers;
        std::unordered_map<item, int> priorityMap;
        struct sortByFrequency;
        bool singlePrefixPath();
        void firstPass(double suppThold);
        void addTransaction(std::vector<item> &transaction, int count);
        void buildFPTree();
        void fpGrowth();
        void printHeadPointers();
};

#endif
