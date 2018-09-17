#include "clustering.h"

using namespace std;

void clustering::readData(string &inFile) {
    FILE* inputStream = fopen(inFile.c_str(), "r");
    vector<double> attributes(MAX_DIM, 0);
    int i = 0;
    while (parseLine(inputStream, attributes, dim)) {
        points.push_back(make_pair(getPoint(attributes), i++));
    }
    fclose(inputStream);
    
    clusterAssmts.resize(points.size());
    fill(clusterAssmts.begin() , clusterAssmts.end(), UNCLASSIFIED);
}