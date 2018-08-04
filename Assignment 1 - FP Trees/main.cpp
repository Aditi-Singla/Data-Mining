#include "apriori.h"
#include "fptree.h"

using namespace std;

int main(int argc, char **argv) {

    string in_file = argv[1];
    double confidence = stod(argv[2]);
    string algorithm = argv[3];
    string out_file = argv[4];

    cout << "Input file : " << in_file << endl;
    cout << "Confidence Threshold : " << confidence << endl;
    cout << "Algorithm : " << algorithm.substr(1) << endl;
    cout << "Writing Results to : " << out_file << endl;

    return 0;
}