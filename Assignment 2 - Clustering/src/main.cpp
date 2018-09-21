#include <iostream>
#include <unordered_map>

#include "io.h"
#include "kmeans.h"
#include "dbscan.h"
#include "optics.h"

using namespace std;

void processClusters(vector<cId> &clusterAssmts, unordered_map<cId, vector<pId>> &clusters) {
    for (pId i = 0; i < clusterAssmts.size(); i++) {
        clusters[clusterAssmts[i]].push_back(i);
    }
}

int main(int argc, char **argv) {

    // faster io
    ios_base::sync_with_stdio(false);

    string inFile = argv[1];
    cout << "Input file : " << inFile << endl;

    // Compute the clusters
    string algorithm = ++argv[2];
    cout << "Algorithm : " << algorithm << endl;
    vector<cId> clusterAssmts;
    bool plotClusters = true;
    if (algorithm == "kmeans") {
        int k = stoi(argv[3]);
        kmeans clusterer(inFile);
        clusterAssmts = clusterer.getClusters(k);
    }
    else if (algorithm == "dbscan") {
        int minPts = stoi(argv[3]);
        double eps = stod(argv[4]);
        dbscan clusterer(inFile);
        clusterAssmts = clusterer.getClusters(minPts, eps);
    }
    else if (algorithm == "optics") {
        int minPts = stoi(argv[3]);
        double eps = stod(argv[4]);
        optics clusterer(inFile);
        plotClusters = false;
        clusterAssmts = clusterer.getClusters(minPts, eps);
        string outFile = algorithm + ".txt";
        cout << "Writing Results to : " << outFile << endl;
        clusterer.writeReachabilityFile(outFile);
    }

    if (plotClusters){
        // process clusters
        unordered_map<cId, vector<pId>> clusters;
        processClusters(clusterAssmts, clusters);

        // write to file
        string outFile = algorithm + ".txt";
        cout << "Writing Results to : " << outFile << endl;
        FILE* outputStream = fopen(outFile.c_str(), "w");
        for (auto it = clusters.begin(); it != clusters.end(); it++) {
            printCluster(it->first, it->second, outputStream);
        }
        fclose(outputStream);
    }
    
    return 0;
}