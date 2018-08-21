#ifndef IO_H
#define IO_H

#include <cstdio>
#include <sstream>
#include <fstream>
#include <iostream>

#include <iterator>
#include <string>

#include <set>
#include <vector>
#include <unordered_map>

typedef int item;
typedef std::vector<item> item_set;

// Input
bool parseLineVec(std::FILE* inFile, std::vector<item> &transaction);
bool parseLineSet(std::FILE* inFile, std::set<item> &transaction);

// Output
void printItemset(item_set itemset, std::FILE* outFile);


#endif