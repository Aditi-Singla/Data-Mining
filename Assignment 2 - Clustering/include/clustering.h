#ifndef CLUSTERING_H
#define CLUSTERING_H

#include <string>

#include "point.h"
#include "io.h"
#include "util.h"

class clustering {

    public :
        std::vector<point> points;
        std::vector<cId> clusterAssmts;

        clustering() {}
        void readPointData(std::string &inFile);
        virtual std::vector<cId> getClusters() {}

    protected:
        std::string inFile;
};

#endif