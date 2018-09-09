#include "dbscan.h"

using namespace std;

dbscan::dbscan(string &inFileName) {

}

void dbscan::setParams(int minPts, double eps) {
    this->minPts = minPts;
    this->eps = eps;
}

unordered_map<cId, vector<pId>> dbscan::getClusters() {
    return clusters;
}