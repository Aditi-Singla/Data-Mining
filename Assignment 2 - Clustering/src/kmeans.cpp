#include "kmeans.h"

using namespace std;

kmeans::kmeans(string &inFileName) {

}

void kmeans::setParams(int k) {
    this->k = k;
}

unordered_map<cId, vector<pId>> kmeans::getClusters() {
    return clusters;
}