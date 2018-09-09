#include "optics.h"

using namespace std;

optics::optics(std::string &inFileName) {

}

void optics::setParams(int minPts, double eps) {
    this->minPts = minPts;
    this->eps = eps;
}

unordered_map<cId, vector<pId>> optics::getClusters() {
    return clusters;
}