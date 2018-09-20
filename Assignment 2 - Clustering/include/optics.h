#ifndef OPTICS_H
#define OPTICS_H

#include <limits>
#include <queue>
#include <bitset>

#include "io.h"
#include "clustering.h"

#define REACHABILITY_DISTANCE_UNDEFINED std::numeric_limits<double>::max()
#define MAKE_POINT_OBJECT(dist, index) index
#define MAX_NUM_PTS 1000000

typedef priority_queue<POINT_OBJECT, vector<POINT_OBJECT>, comparePoint> PRIORITY_QUEUE;
typedef bitset<MAX_NUM_PTS> SET_TYPE;

class optics : private clustering {
		rtree rTree;
    public :
        optics(): rTree(){}
        optics(std::string &inFileName);
        // void getReachability(int minPts, double maxEps);
        std::vector<cId> getClusters(int minPts, double maxEps);
        void expandCluster(int startPtIndex, double eps, int minPts);
        double getCoreDistance(int ptIndex, double eps, int minPts);
        void update(PRIORITY_QUEUE &orderSeeds, int &numEltsInSeeds, 
        	vector<vector<int> > &epsilonNeighbourhoodMatrix, int ptIndex, SET_TYPE &seedIndices);
        
        void writeReachabilityFile(std::string &tempFileName, double eps);

    private :
        std::vector<double> reachabilityDistances;
        std::vector<double> coreDistances;
        std::vector<int> orderedList;
};

#endif