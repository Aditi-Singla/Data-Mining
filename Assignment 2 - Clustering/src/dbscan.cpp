#include "dbscan.h"

#include <iostream>

using namespace std;

dbscan::dbscan(string &inFileName) {
    inFile = inFileName;
    dbscan::readData(inFile);
}

void dbscan::expandCluster(value& startPt, cId clusterID, double eps, int minPts) {

}

vector<cId> dbscan::getClusters(int minPts, double eps) {
    // Clusters noise as -1

    cId currCluster = 0;

    for (int i = 0; i < points.size(); i++) {
        switch(clusterAssmts[i]) {
            case UNCLASSIFIED:
                expandCluster(points[i], currCluster, eps, minPts);
            default:
                break;
        }
    }

    return clusterAssmts;
}

