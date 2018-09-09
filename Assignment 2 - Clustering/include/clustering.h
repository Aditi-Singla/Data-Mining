#ifndef CLUSTERING_H
#define CLUSTERING_H

#include <unordered_map>

#include "point.h"

typedef int cId;

class clustering {

    public :
        std::unordered_map<cId, std::vector<pId>> clusters;

        clustering() {}
        virtual std::unordered_map<cId, std::vector<pId>> getClusters() = 0;
};

#endif