#include "kmeans.h"

using namespace std;

kmeans::kmeans(std::vector<point> *data) {
    points = *data;
    assignments.resize(points.size());
    fill(assignments.begin() , assignments.end(), -1);
}

unordered_map<cId, vector<pId>> kmeans::getClusters(int k) {
    return clusters;
}