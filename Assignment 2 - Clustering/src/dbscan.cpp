#include "dbscan.h"

using namespace std;

dbscan::dbscan(std::vector<point> &data) {
    points = &data;
    assignments.resize(points->size());
    fill(assignments.begin() , assignments.end(), -1);
}

unordered_map<cId, vector<pId>> dbscan::getClusters(int minPts, double eps) {
    cId currCluster = 0;
    // for (int i = 0; i < points.size(); i++) {
    //     if (assignments[i] == -1) {

    //     }
    // }
    return clusters;
}