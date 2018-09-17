#ifndef DBSCAN_H
#define DBSCAN_H

#include "clustering.h"

class dbscan : private clustering {

    public :
        dbscan() {}
        dbscan(std::string &inFileName);
        std::vector<cId> getClusters(int minPts, double eps);

        // void readData(std::string &inFile);

};

#endif