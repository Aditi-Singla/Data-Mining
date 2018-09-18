#ifndef OPTICS_H
#define OPTICS_H

#include "io.h"
#include "clustering.h"

class optics : private clustering {
		rtree rTree;
    public :
        optics(): rTree(){}
        optics(std::string &inFileName);
        void getReachability(int minPts, double maxEps);
        std::vector<cId> getClusters(int minPts, double maxEps);

    private :
        std::vector<double> reachabilityDistances;

        void writeReachabilityFile(std::string &tempFileName);

};

#endif