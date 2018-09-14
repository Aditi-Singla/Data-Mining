#include "optics.h"

using namespace std;

optics::optics(string &inFileName) {
    inFile = inFileName;
    readData(inFile);
}

void optics::readData(string &inFile) {
    FILE* inputStream = fopen(inFile.c_str(), "r");
    vector<double> attributes;
    int i = 0;
    while (parseLine(inputStream, attributes, attributes.size())) {
        point pt(i++, attributes);

        points.push_back(pt);
    }
    fclose(inputStream);
    
    clusterAssmts.resize(points.size());
    fill(clusterAssmts.begin() , clusterAssmts.end(), -1);
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