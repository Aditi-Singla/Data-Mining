#ifndef FPTREE_H
#define FPTREE_H

#include <set>
#include <unordered_set>

#include "fiMiner.h"

class fpNode {
    public:
        int item;
        int count;      
        fpNode* next;   // next item in the linked list
        fpNode* parent;
        std::unordered_map<int, fpNode*> children; // item to fpNode*
        fpNode();
        fpNode(int i, int c);
        fpNode(int i, fpNode* p);
        fpNode(int i, int c, fpNode* p);
        std::vector<int> getTransaction();
};

class fpTree : public fiMiner {

    public:
        fpNode* root;
        fpTree(std::string &inFileName);
        fpTree(int rawSupportThreshold);
        std::vector<item_set> getFrequentItemsets(double suppThold);
        std::vector<item_set> getFrequentItemsets();
        
    private:
        int numTransactions, rawSuppThold;
        std::unordered_map<int, fpNode*> headPointers;
        std::unordered_map<int, fpNode*> currPointers;
        std::unordered_map<int, int> priorityMap;
        struct sortByFrequency;
        bool singlePrefixPath();
        void firstPass(double suppThold);
        void buildFPTree();
        void fpGrowth();
        void addTransaction(std::vector<int> &transaction, int count, bool priorityCheck);
        void printHeadPointers();

};

#endif
