#ifndef IO_H
#define IO_H

#include <iostream>
#include <vector>
#include <cstdio>

#include "point.h"
#include "util.h"

// Input
bool parseLine(std::FILE* inFile, std::vector<double> &attributes, int size);

// Output
void printCluster(cId clusterID, std::vector<pId> &pointIDs, std::FILE* outFile);
void printVector(std::vector<double> &yValues, std::FILE* outFile);

#endif