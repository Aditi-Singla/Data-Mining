#include "clustering.h"

using namespace std;

void clustering::readData(string &inFile) {
    FILE* inputStream = fopen(inFile.c_str(), "r");
    vector<double> attributes;
    int i = 0;
    while (parseLine(inputStream, attributes, attributes.size())) {
        points.push_back(point(i++, attributes));
    }
    fclose(inputStream);
    
    clusterAssmts.resize(points.size());
    fill(clusterAssmts.begin() , clusterAssmts.end(), -1);
}