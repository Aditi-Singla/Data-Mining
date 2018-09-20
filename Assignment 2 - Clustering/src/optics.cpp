#include <cmath>

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

double optics::getCoreDistance(int ptIndex, double eps, int minPts) {
    vector<vector<int> > neighbourhoodMatrix;
    vector<vector<double> > sqDistanceMatrix;
    rTree.getKNN(neighbourhoodMatrix, sqDistanceMatrix, points, ptIndex*dim, dim, minPts);

    // Check if the distance of the minPts'th neighbour is < epsilon or not

    if (sqDistanceMatrix[0][minPts - 1] > eps*eps){
        return REACHABILITY_DISTANCE_UNDEFINED;
    }
    
    return sqrt(sqDistanceMatrix[0][minPts - 1]);
}

void optics::update(PRIORITY_QUEUE &orderSeeds, int &numEltsInSeeds, 
            vector<vector<int> > &epsilonNeighbourhoodMatrix, int ptIndex, unordered_set<int> &seedIndices) {

    double coreDist = coreDistances[ptIndex];
    for (int i = 1; i < epsilonNeighbourhoodMatrix[0].size(); i++) {
        int headPtIndex = epsilonNeighbourhoodMatrix[0][i];
        if (clusterAssmts[headPtIndex] == UNCLASSIFIED) {
            double newReachabilityDist = max(coreDist, sqrt(sqDistance(points, ptIndex, headPtIndex, dim)));
            if (reachabilityDistances[headPtIndex] == REACHABILITY_DISTANCE_UNDEFINED) {
                reachabilityDistances[headPtIndex] = newReachabilityDist;

                orderSeeds.push(MAKE_POINT_OBJECT(newReachabilityDist, headPtIndex));
                seedIndices.insert(headPtIndex);
            }
            else {
                if (newReachabilityDist < reachabilityDistances[headPtIndex]) {
                    reachabilityDistances[headPtIndex] = newReachabilityDist;
                    // Instead of update, insert a new one with less priority
                    // and don't increment the numEltsInSeeds
                    orderSeeds.push(MAKE_POINT_OBJECT(newReachabilityDist, headPtIndex));
                }
            }
        }
    }
}

void optics::expandCluster(int startPtIndex, double eps, int minPts) {
    // Fetch epsilon neighbourhood
    vector<vector<int> > epsilonNeighbourhoodMatrix;
    PRIORITY_QUEUE orderSeeds(&reachabilityDistances[0]);
    unordered_set<int> seedIndices;

    // A priority_queue cannot efficiently provide a move_up function. Hence to overcome that,
    // lazy deletion has been used. Thus, to check if the seeds are empty, we use the counter
    // which will get updated only at the time of insertion or deletion.
    int numEltsInSeeds = 0;
    
    rTree.getEpsilonNeighbourhood(epsilonNeighbourhoodMatrix, points, startPtIndex*dim, dim, eps);
    clusterAssmts[startPtIndex] = CLASSIFIED;
    reachabilityDistances[startPtIndex] = REACHABILITY_DISTANCE_UNDEFINED;
    coreDistances[startPtIndex] = getCoreDistance(startPtIndex, eps, minPts);

    // Add to ordered file
    orderedList.push_back(startPtIndex);

    if (coreDistances[startPtIndex] != REACHABILITY_DISTANCE_UNDEFINED) {
        update(orderSeeds, numEltsInSeeds, epsilonNeighbourhoodMatrix, startPtIndex, seedIndices);
        while (seedIndices.size()) {
            epsilonNeighbourhoodMatrix.clear();

            POINT_OBJECT currObj = orderSeeds.top();
            orderSeeds.pop();
            int ptIndex = currObj;
            
            while (seedIndices.find(ptIndex) == seedIndices.end()) {
                currObj = orderSeeds.top();
                orderSeeds.pop();
                ptIndex = currObj;    
            }

            // Empty seed indices
            seedIndices.erase(ptIndex);
            
            rTree.getEpsilonNeighbourhood(epsilonNeighbourhoodMatrix, points, ptIndex*dim, dim, eps);
            clusterAssmts[ptIndex] = CLASSIFIED;
            coreDistances[ptIndex] = getCoreDistance(ptIndex, eps, minPts);

            orderedList.push_back(ptIndex);
            
            if (coreDistances[ptIndex] != REACHABILITY_DISTANCE_UNDEFINED) {
                update(orderSeeds, numEltsInSeeds, epsilonNeighbourhoodMatrix, ptIndex, seedIndices);
            }
        }
    }
}

vector<cId> optics::getClusters(int minPts, double maxEps) {
    
    for (int i = 0; i*dim < points.size(); i++) {
        switch(clusterAssmts[i]) {
            case UNCLASSIFIED:
                expandCluster(i, maxEps, minPts);
            default:
                break;
        }
    }

    return clusterAssmts;
}

void optics::writeReachabilityFile(string &tempFileName, double maxEps) {
    FILE* outputStream = fopen(tempFileName.c_str(), "w");
    for (int i = 0; i < orderedList.size(); i++){
        printInt(i, outputStream);
        fputc_unlocked(' ', outputStream);
        if (reachabilityDistances[orderedList[i]] == REACHABILITY_DISTANCE_UNDEFINED)
            printDouble(maxEps, outputStream);
        else
            printDouble(reachabilityDistances[orderedList[i]], outputStream);
    }
    cout << endl;
    fclose(outputStream);
}