#ifndef CLUSTERING_H
#define CLUSTERING_H

#include <string>

#include "point.h"
#include "io.h"
#include "util.h"

class clustering {

    public :
    	int dim; // dimensions of the point space
        std::vector<point> points;
        std::vector<cId> clusterAssmts;

        clustering(): dim(-1){}
        void readData(std::string &inFile);
        virtual std::vector<cId> getClusters() {}

    protected :
        std::string inFile;
};

#endif