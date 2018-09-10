#include "dbscan.h"

using namespace std;

dbscan::dbscan(std::vector<point> &data) {

}

unordered_map<cId, vector<pId>> dbscan::getClusters(int minPts, double eps) {
    return clusters;
}