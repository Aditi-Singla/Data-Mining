#ifndef DBSCAN_H
#define DBSCAN_H

#include "clustering.h"

class dbscan : private clustering {
		rtree rTree;
    public :
        dbscan(): rTree(){}
        dbscan(std::string &inFileName);
        bool expandCluster(int startPtIndex, cId clusterID, double eps, int minPts);
        std::vector<cId> getClusters(int minPts, double eps);
};

#endif