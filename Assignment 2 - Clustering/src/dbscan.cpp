#include "dbscan.h"

#include <iostream>
#include <queue>

using namespace std;

dbscan::dbscan(string &inFileName): rTree() {
    inFile = inFileName;
    readData(inFile);

    // bulk load the RTree
    rTree.bulkLoad(points);
}

bool dbscan::expandCluster(value& startPtValue, cId clusterID, double eps, int minPts) {
    point startPt = startPtValue.first;
    int startPtIndex = startPtValue.second;

    // Fetch epsilon neighbourhood
    std::vector<value> epsilonNeighbourhood;
    queue<int> bfsQueue;
    
    rTree.getEpsilonNeighbourhood(epsilonNeighbourhood, startPt, eps);

    // for (int i = 0; i<epsilonNeighbourhood.size(); i++) {
    //     cout << epsilonNeighbourhood[i].second << " ";
    // }
    // cout<<"\n";

    if (epsilonNeighbourhood.size() < minPts) {
        clusterAssmts[startPtIndex] = NOISE;
        return false;
    }
    else {
        // cout << "INSIDE TRUE BRANCH!! ";
        for (int i = 0; i < epsilonNeighbourhood.size(); i++) {
            int ptId = epsilonNeighbourhood[i].second;
            clusterAssmts[ptId] = clusterID;

            // delete the point itself from the epsilon neighbourhood and push all the others in the queue for bfs
            if (ptId != startPtIndex) {
                bfsQueue.push(ptId);
            }
        }

        while (!bfsQueue.empty()) {
            epsilonNeighbourhood.clear();
            point headPoint = points[bfsQueue.front()].first;
            rTree.getEpsilonNeighbourhood(epsilonNeighbourhood, headPoint, eps);

            if (epsilonNeighbourhood.size() >= minPts) {
                for (int j = 1; j < epsilonNeighbourhood.size(); j++) {
                    point tempPt = epsilonNeighbourhood[j].first;
                    int tempPtIndex = epsilonNeighbourhood[j].second;
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

    for (int i = 0; i < points.size(); i++) {
        // std::cout << currCluster << " ";
        switch(clusterAssmts[i]) {
            case UNCLASSIFIED:
                currCluster = (expandCluster(points[i], currCluster, eps, minPts)? currCluster+1 : currCluster);
            default:
                break;
        }
    }

    return clusterAssmts;
}

