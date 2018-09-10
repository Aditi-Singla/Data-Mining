#ifndef DBSCAN_H
#define DBSCAN_H

#include "clustering.h"

class dbscan : public clustering {

    public :
        dbscan() {}
        dbscan(std::vector<point> &data);
        std::unordered_map<cId, std::vector<pId>> getClusters(int minPts, double eps);

    private : 
        int minPts;
        double eps;
        
};

#endif