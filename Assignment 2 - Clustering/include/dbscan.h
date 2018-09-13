#ifndef DBSCAN_H
#define DBSCAN_H

#include <algorithm>

#include "clustering.h"

class dbscan : private clustering {

    public :
        dbscan() {}
        dbscan(std::string &inFileName);
        std::vector<cId> getClusters(int minPts, double eps);

};

#endif