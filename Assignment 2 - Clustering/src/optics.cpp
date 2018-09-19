#include "optics.h"

using namespace std;

optics::optics(string &inFileName) {
    inFile = inFileName;
    readData(inFile);

    // bulk load the RTree
    rTree.bulkLoad(points, dim);
    
    // Initialise core and reachability distances
    coreDistances.resize(points.size()/dim);
    fill(coreDistances.begin(), coreDistances.end(), REACHABILITY_DISTANCE_UNDEFINED);

    reachabilityDistances.resize(points.size()/dim);
    fill(reachabilityDistances.begin(), reachabilityDistances.end(), REACHABILITY_DISTANCE_UNDEFINED);
}

void optics::expandCluster(int startPtIndex, double eps, int minPts) {
    // Fetch epsilon neighbourhood
    vector<vector<int> > epsilonNeighbourhoodMatrix;
    priority_queue<POINT_OBJECT> orderSeeds;
    
    rTree.getEpsilonNeighbourhood(epsilonNeighbourhoodMatrix, points, startPtIndex*dim, dim, eps);
    clusterAssmts[startPtIndex] = CLASSIFIED;
    double reachabilityDistance = setCoreDistance(startPtIndex, epsilonNeighbourhoodMatrix, eps, minPts);
    POINT_OBJECT obj = MAKE_POINT_OBJECT(reachabilityDistance, startPtIndex);
    reachabilityDistances.push_back(reachabilityDistance);

    if (obj.first != REACHABILITY_DISTANCE_UNDEFINED) {

    	update(orderSeeds, epsilonNeighbourhoodMatrix, obj);
    	while (!orderSeeds.empty()) {
    		epsilonNeighbourhoodMatrix.clear();
    		POINT_OBJECT &currObj = orderSeeds.front();
    		startPtIndex = currObj.second;
    		rTree.getEpsilonNeighbourhood(epsilonNeighbourhoodMatrix, points, startPtIndex*dim, dim, eps);
    		clusterAssmts[startPtIndex] = CLASSIFIED;
			reachabilityDistance = setCoreDistance(startPtIndex, epsilonNeighbourhoodMatrix, eps, minPts);
    		POINT_OBJECT obj = MAKE_POINT_OBJECT(reachabilityDistance, startPtIndex);
    		reachabilityDistances.push_back(reachabilityDistance);
    	}
    }
    


        for (int i = 0; i < epsilonNeighbourhood.size(); i++) {
            int ptId = epsilonNeighbourhood[i];
            clusterAssmts[ptId] = clusterID;

            // delete the point itself from the epsilon neighbourhood and push all the others in the queue for bfs
            if (ptId != startPtIndex) {
                bfsQueue.push(ptId);
            }
        }

        while (!bfsQueue.empty()) {
            epsilonNeighbourhoodMatrix.clear();
            int headPointIndex = bfsQueue.front();
            rTree.getEpsilonNeighbourhood(epsilonNeighbourhoodMatrix, points, headPointIndex*dim, dim, eps);

            // IMPORTANT: We have only one query and hence the epsilon neighbourhood will be a row 2D matrix
            vector<int> &epsilonNeighbourhood = epsilonNeighbourhoodMatrix[0];

            if (epsilonNeighbourhood.size() >= minPts) {
                for (int j = 1; j < epsilonNeighbourhood.size(); j++) {
                    int tempPtIndex = epsilonNeighbourhood[j];
                    int tempPtClusterAssmt = clusterAssmts[tempPtIndex];
                    if (tempPtClusterAssmt < 0) {
                        if (tempPtClusterAssmt == UNCLASSIFIED) {
                            bfsQueue.push(tempPtIndex);
                        }
                        clusterAssmts[tempPtIndex] = clusterID;
                    }
                }
            }

            bfsQueue.pop();
        }

        return true;
    }
}

vector<cId> optics::getClusters(int minPts, double maxEps) {
    
	for (int i = 0; i*dim < points.size(); i++) {
        switch(clusterAssmts[i]) {
            case UNCLASSIFIED:
                expandCluster(i, eps, minPts);
            default:
                break;
        }
    }

    return clusterAssmts;
}

void optics::writeReachabilityFile(string &tempFileName) {
    FILE* outputStream = fopen(tempFileName.c_str(), "w");
    printVector(reachabilityDistances, outputStream);
    fclose(outputStream);
}