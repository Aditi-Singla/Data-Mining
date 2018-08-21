#ifndef INPUT_H
#define INPUT_H

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
std::set<int> parseLine(std::string &line);
std::vector<int> parseLineVec(std::string &line);

// Output
void printItemset(item_set itemset, std::FILE* outFile);


#endif