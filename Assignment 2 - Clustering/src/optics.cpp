#include "optics.h"

using namespace std;

optics::optics(std::vector<point> &data) {

}

void optics::writeReachabilityFile(string tempFile) {
    FILE* outputStream = fopen(tempFile.c_str(), "w");
    printVector(reachabilityDistances, outputStream);
    fclose(outputStream);
}

unordered_map<cId, vector<pId>> optics::getClusters(int minPts, double eps) {
    return clusters;
}