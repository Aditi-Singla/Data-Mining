#ifndef DBSCAN_H
#define DBSCAN_H

#include "clustering.h"

class dbscan : public clustering {

    public :
        dbscan() {}
        dbscan(std::string &inFileName);
        void setParams(int minPts, double eps);
        std::unordered_map<cId, std::vector<pId>> getClusters();

    private : 
        int minPts;
        double eps;
        
};

#endif