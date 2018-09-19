#include "kmeans.h"

#define MAX_ITERATIONS 100000

using namespace std;

kmeans::kmeans(string &inFileName) {
    inFile = inFileName;
    readData(inFile);
}

vector<cId> kmeans::getClusters(int k) {

    int numPoints = points.size()/dim;

    // TODO: Do we need this?
    k = min(k, numPoints);

    vector<vector<double>> centroids(k);
    vector<vector<double>> sumCluster(k, vector<double>(dim, 0));
    vector<int> countCluster(k, 0);

    // Choose k points as centroids
    for (int i = 0; i < k; i++) {
        int index = i*dim*(numPoints/k);
        centroids[i] = vector<double>(points.begin()+index, points.begin()+index+dim);
    }

    int iterations = 0;
    vector<double> point;
    double minDistance, dist, cluster;

    while (iterations < MAX_ITERATIONS) {

        // Reassign cluster ids to points
        bool cont = false;
        for (int j = 0; j < numPoints; j ++) {
            minDistance = -1;
            for (int i = 0; i < k; i++) {
                dist = distanceVec(centroids[i], points, j*dim);
                if (minDistance < 0 || dist < minDistance) {
                    minDistance = dist;
                    cluster = i;
                }
            }
            if (clusterAssmts[j] != cluster){
                clusterAssmts[j] = cluster;
                cont = true;
            }
            auto &sum = sumCluster[cluster];
            transform(sum.begin(), sum.end(), points.begin() + j*dim, sum.begin(), std::plus<double>());
            countCluster[cluster]++;
        }

        // Update Cluster Means
        for (int i = 0; i < k; i++) {
            for (auto &c: sumCluster[i])
                c /= countCluster[i];
            centroids[i] = sumCluster[i];
        }

        if (!cont) break;
        iterations++;
        fill(countCluster.begin(), countCluster.end(), 0);
        for (auto &c: sumCluster){
            fill(c.begin(), c.end(), 0);
        }
    }

    return clusterAssmts;
}