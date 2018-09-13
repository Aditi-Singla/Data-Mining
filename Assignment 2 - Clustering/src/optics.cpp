#include "optics.h"

using namespace std;

optics::optics(string &inFileName) {
    inFile = inFileName;
    readPointData(inFile);
}

void optics::getReachability(int minPts, double maxEps) {

}

vector<cId> optics::getClusters(int minPts, double maxEps) {
    return clusterAssmts;
}

void optics::writeReachabilityFile(string &tempFileName) {
    FILE* outputStream = fopen(tempFileName.c_str(), "w");
    printVector(reachabilityDistances, outputStream);
    fclose(outputStream);
}