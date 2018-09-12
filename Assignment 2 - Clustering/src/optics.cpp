#include "optics.h"

using namespace std;

optics::optics(std::vector<point> *data) {
    points = *data;
    assignments.resize(points.size());
    fill(assignments.begin() , assignments.end(), -1);
}

void optics::writeReachabilityFile(string tempFile) {
    FILE* outputStream = fopen(tempFile.c_str(), "w");
    printVector(reachabilityDistances, outputStream);
    fclose(outputStream);
}

unordered_map<cId, vector<pId>> optics::getClusters(int minPts, double eps) {
    return clusters;
}