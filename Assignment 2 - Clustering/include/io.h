#ifndef IO_H
#define IO_H

#include <cstdio>
#include <fstream>
#include <vector>
#include <unordered_map>

#include "point.h"
#include "clustering.h"

// Input
bool parseLine(std::FILE* inFile, point &pt);

// Output
void printCluster(cId clusterID, std::vector<pId> &pointIDs, std::FILE* outFile);

#endif