#include "kmeans.h"

using namespace std;

kmeans::kmeans(string &inFileName) {
    inFile = inFileName;
    readPointData(inFile);
}

vector<cId> kmeans::getClusters(int k) {

    return clusterAssmts;
}