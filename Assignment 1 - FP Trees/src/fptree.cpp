#include "fpTree.h"

using namespace std;

fpTree::fpTree(string &inFileName) {
    inFile = inFileName;
}

vector<item_set> fpTree::getFrequentItemsets(double suppThold) {
    return freqItemsets;
}