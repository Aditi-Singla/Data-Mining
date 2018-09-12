#include <iostream>

#include "io.h"
#include "kmeans.h"
#include "dbscan.h"
#include "optics.h"

using namespace std;

int main(int argc, char **argv) {

    // faster io
    ios_base::sync_with_stdio(false);

    // read from file
    string inFile = argv[1];
    cout << "Input file : " << inFile << endl;
    vector<point> data;
    FILE* inputStream = fopen(inFile.c_str(), "r");
    readData(inputStream, data);

    // Compute the clusters
    string algorithm = argv[2];
    cout << "Algorithm : " << algorithm << endl;
    unordered_map<cId, vector<pId>> clusters;
    if (algorithm == "kmeans") {
        int k = stoi(argv[3]);
        kmeans clusterer(&data);
        clusters = clusterer.getClusters(k);
    }
    else if (algorithm == "dbscan") {
        int minPts = stoi(argv[3]);
        double eps = stod(argv[4]);
        dbscan clusterer(&data);
        clusters = clusterer.getClusters(minPts, eps);
    }
    else if (algorithm == "optics") {
        int minPts = stoi(argv[3]);
        double eps = stod(argv[4]);
        optics clusterer(&data);
        clusters = clusterer.getClusters(minPts, eps);
     }

    // write to file
    string outFile = algorithm + ".txt";
    cout << "Writing Results to : " << outFile << endl;
    FILE* outputStream = fopen(outFile.c_str(), "w");
    for (auto it = clusters.begin(); it != clusters.end(); it++) {
        printCluster(it->first, it->second, outputStream);
    }
    fclose(outputStream);

    point p1 = data[0];
    for (point &p : data) {
        for (double d : p.attributes) {
            cout << d << ' ';
        }
        cout << distance(p, p1);
        cout << endl;
    }

    return 0;
}