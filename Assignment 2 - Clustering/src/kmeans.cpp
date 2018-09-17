#include "kmeans.h"

#define MAX_ITERATIONS 100000

using namespace std;

kmeans::kmeans(string &inFileName) {
    inFile = inFileName;
    readData(inFile);
}

vector<cId> kmeans::getClusters(int k) {

    int ptsize = points.size();

    // TODO: Do we need this?
    k = min(k, ptsize);

    vector<vector<double>> centroids(k, vector<double>(MAX_DIM, 0));
    vector<vector<double>> sumCluster(k, vector<double>(MAX_DIM, 0));
    vector<int> countCluster(k, 0);

    // Choose k points as centroids
    for (int i = 0; i < k; i++) {
        setPoint(points[i*ptsize/k].first, centroids[i]);
    }

    int iterations = 0;
    vector<double> point;
    double minDistance, dist, cluster;

    while (iterations < MAX_ITERATIONS) {

        // Reassign cluster ids to points
        bool cont = false;
        for (int j = 0; j < ptsize; j++) {
            minDistance = -1;
            setPoint(points[j].first, point);
            for (int i = 0; i < k; i++) {
                dist = distanceVec(point, centroids[i]);
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
            transform(sum.begin(), sum.end(), point.begin(), sum.begin(), std::plus<double>());
            countCluster[cluster]++;
        }

        // Update Cluster Means
        for (int i = 0; i < k; i++) {
            centroids[i] = sumCluster[i];
            for (auto &c: centroids[i])
                c /= countCluster[i];
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