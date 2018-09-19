#ifndef OPTICS_H
#define OPTICS_H

#include <limits>

#include "io.h"
#include "clustering.h"

#define REACHABILITY_DISTANCE_UNDEFINED std::numeric_limits<double>::max()

typedef std::pair<double, int> POINT_OBJECT;

#define MAKE_POINT_OBJECT(dist, index) std::make_pair(dist, index)

class optics : private clustering {
		rtree rTree;
    public :
        optics(): rTree(){}
        optics(std::string &inFileName);
        void getReachability(int minPts, double maxEps);
        std::vector<cId> getClusters(int minPts, double maxEps);
        bool expandCluster(int startPtIndex, cId clusterID, double eps, int minPts);

    private :
        std::vector<double> reachabilityDistances;

        void writeReachabilityFile(std::string &tempFileName);

};

#endif