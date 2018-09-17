#include "clustering.h"

using namespace std;

inline point setPoint(vector<double> &attributes) {
	point pt;
	// for (int i = 0; i < MAX_DIM; ++i) {
	// 	pt.set<i>(attributes[i]);
	// }
	pt.set<0>(attributes[0]);
	pt.set<1>(attributes[1]);
	pt.set<2>(attributes[2]);
	pt.set<3>(attributes[3]);
	pt.set<4>(attributes[4]);
	return pt;
}

void clustering::readData(string &inFile) {
    FILE* inputStream = fopen(inFile.c_str(), "r");
    vector<double> attributes(MAX_DIM, 0);
    int i = 0;
    while (parseLine(inputStream, attributes, dim)) {
        points.push_back(setPoint(attributes));
    }
    fclose(inputStream);
    
    clusterAssmts.resize(points.size());
    fill(clusterAssmts.begin() , clusterAssmts.end(), -1);
}