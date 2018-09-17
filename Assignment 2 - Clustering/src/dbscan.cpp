#include "dbscan.h"

#include <iostream>

using namespace std;

dbscan::dbscan(string &inFileName) {
    inFile = inFileName;
    dbscan::readData(inFile);
}

vector<cId> dbscan::getClusters(int minPts, double eps) {
    cId currCluster = 0;
    // for (int i = 0; i < points.size(); i++) {
    //     if (assignments[i] == -1) {

    //     }
    // }
    return clusterAssmts;
}

