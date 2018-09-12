#ifndef CLUSTERING_H
#define CLUSTERING_H

#include <unordered_map>

#include "point.h"
#include "util.h"

typedef int cId;

class clustering {

    public :
        std::vector<point> points;
        std::unordered_map<cId, std::vector<pId>> clusters;

        clustering() {}
        virtual std::unordered_map<cId, std::vector<pId>> getClusters() {}

    protected:
        std::vector<cId> assignments;
};

#endif