#include "dbscan.h"

#include <iostream>

using namespace std;

dbscan::dbscan(string &inFileName) {
    inFile = inFileName;
    dbscan::readData(inFile);
}

void dbscan::readData(string &inFile) {
    FILE* inputStream = fopen(inFile.c_str(), "r");
    vector<double> attributes;
    int i = 0;
    while (parseLine(inputStream, attributes, attributes.size())) {
        point pt(i++, attributes);

        points.push_back(pt);
    }
    fclose(inputStream);
    
    clusterAssmts.resize(points.size());
    fill(clusterAssmts.begin() , clusterAssmts.end(), -1);
}


vector<cId> dbscan::getClusters(int minPts, double eps) {
    cId currCluster = 0;
    // for (int i = 0; i < points.size(); i++) {
    //     if (assignments[i] == -1) {

    //     }
    // }
    return clusterAssmts;
}

