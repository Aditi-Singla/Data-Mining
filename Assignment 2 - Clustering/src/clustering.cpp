#include "clustering.h"

using namespace std;

void clustering::readPointData(string &inFile) {
    FILE* inputStream = fopen(inFile.c_str(), "r");
    readData(inputStream, points);
    
    clusterAssmts.resize(points.size());
    fill(clusterAssmts.begin() , clusterAssmts.end(), -1);
}