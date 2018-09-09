#include <iostream>

#include "io.h"
#include "kmeans.h"
#include "dbscan.h"
#include "optics.h"

using namespace std;

int main(int argc, char **argv) {

    // faster io
    ios_base::sync_with_stdio(false);

    string inFile = argv[1];
    string algorithm = argv[2];
    string outFile = algorithm + ".txt";

    cout << "Input file : " << inFile << endl;
    cout << "Algorithm : " << algorithm << endl;

    unordered_map<cId, vector<pId>> clusters;
    if (algorithm == "kmeans") {
        int k = stoi(argv[3]);
        kmeans clusterer(inFile);
        clusterer.setParams(k);
        clusters = clusterer.getClusters();
    }
    else if (algorithm == "dbscan") {
        int minPts = stoi(argv[3]);
        double eps = stod(argv[4]);
        dbscan clusterer(inFile);
        clusterer.setParams(minPts, eps);
        clusters = clusterer.getClusters();
    }
    else if (algorithm == "optics") {
        int minPts = stoi(argv[3]);
        double eps = stod(argv[4]);
        optics clusterer(inFile);
        clusterer.setParams(minPts, eps);
        clusters = clusterer.getClusters();
     }

    // write to file
    cout << "Writing Results to : " << outFile << endl;
    FILE* outputStream = fopen(outFile.c_str(), "w");
    for (auto it = clusters.begin(); it != clusters.end(); it++) {
        printCluster(it->first, it->second, outputStream);
    }
    fclose(outputStream);

    return 0;
}