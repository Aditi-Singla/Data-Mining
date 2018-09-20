#include "dbscan.h"

#include <iostream>
#include <queue>

using namespace std;

dbscan::dbscan(string &inFileName): rTree() {
    inFile = inFileName;
    readData(inFile);

    // bulk load the RTree
    rTree.bulkLoad(points, dim);
}

bool dbscan::expandCluster(int startPtIndex, cId clusterID, double eps, int minPts) {
    // Fetch epsilon neighbourhood
    vector<vector<int> > epsilonNeighbourhoodMatrix;
    queue<int> bfsQueue;
    
    rTree.getEpsilonNeighbourhood(epsilonNeighbourhoodMatrix, points, startPtIndex*dim, dim, eps);

    // IMPORTANT: We have only one query and hence the epsilon neighbourhood will be a row 2D matrix
    vector<int> &epsilonNeighbourhood = epsilonNeighbourhoodMatrix[0];
    if (epsilonNeighbourhood.size() < minPts) {
        clusterAssmts[startPtIndex] = NOISE;
        return false;
    }
    else {
        for (int i = 0; i < epsilonNeighbourhood.size(); i++) {
            int ptId = epsilonNeighbourhood[i];
            clusterAssmts[ptId] = clusterID;

            // delete the point itself from the epsilon neighbourhood and push all the others in the queue for bfs
            if (ptId != startPtIndex) {
                bfsQueue.push(ptId);
            }
        }

        while (!bfsQueue.empty()) {
            // epsilonNeighbourhoodMatrix.clear();
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

vector<cId> dbscan::getClusters(int minPts, double eps) {
    // Clusters noise as -1

    cId currCluster = 0;

    for (int i = 0; i*dim < points.size(); i++) {
        switch(clusterAssmts[i]) {
            case UNCLASSIFIED:
                currCluster = (expandCluster(i, currCluster, eps, minPts)? currCluster+1 : currCluster);
            default:
                break;
        }
    }

    return clusterAssmts;
}

