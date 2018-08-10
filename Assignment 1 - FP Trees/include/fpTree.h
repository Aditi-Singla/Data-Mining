#ifndef FPTREE_H
#define FPTREE_H

#include "fiMiner.h"

class fpNode {
    public:
        int item;
        int count;      
        fpNode* next;   // next item in the linked list
        fpNode* parent;
        std::unordered_set<fpNode*> children;
        fpNode();
        fpNode(int i, int c);
        fpNode(int i, fpNode* p);
        fpNode(int i, int c, fpNode* p);
};

class fpTree : public fiMiner {

    public:
        fpNode* root;
        fpTree(std::string &inFileName);
        std::vector<item_set> getFrequentItemsets(double suppThold);

    private:
        int numTransactions;
        std::unordered_map<int, fpNode*> headPointers;
        std::unordered_map<int, fpNode*> currPointers;
        std::unordered_map<int, int> priorityMap;
        struct sortByFrequency;
        void firstPass(double suppThold);
        void initialiseTree();
        void buildFPTree();
};

#endif