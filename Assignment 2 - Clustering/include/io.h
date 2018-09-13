#ifndef IO_H
#define IO_H

#include <vector>
#include <cstdio>

#include "point.h"
#include "util.h"

// Input
void readData(std::FILE* inFile, std::vector<point> &data);

// Output
void printCluster(cId clusterID, std::vector<pId> &pointIDs, std::FILE* outFile);
void printVector(std::vector<double> &yValues, std::FILE* outFile);

#endif