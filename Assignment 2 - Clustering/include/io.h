#ifndef IO_H
#define IO_H

#include <cstdio>
#include <fstream>
#include <vector>
#include <unordered_map>

#include "point.h"
#include "clustering.h"

// Input
void readData(std::FILE* inFile, std::vector<point> &data);

// Output
void printCluster(cId clusterID, std::vector<pId> &pointIDs, std::FILE* outFile);
void printVector(std::vector<double> &yValues, std::FILE* outFile);

#endif