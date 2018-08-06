#ifndef APRIORI_H
#define APRIORI_H

#include "Input.h"

std::vector<item_set> freqItemsetsApriori(std::string &inFile, double suppThold);

#endif