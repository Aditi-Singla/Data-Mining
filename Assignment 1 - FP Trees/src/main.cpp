#include "apriori.h"
#include "fpTree.h"

using namespace std;

int main(int argc, char **argv) {

    // faster io
    ios_base::sync_with_stdio(false);

    string inFile = argv[1];
    double suppThold = stod(argv[2]);
    string algorithm = argv[3];
    string outFile = argv[4];

    cout << "Input file : " << inFile << endl;
    cout << "Support Threshold : " << suppThold << endl;
    cout << "Algorithm : " << algorithm << endl;

    std::vector<item_set> frequentItemsets;
    if (algorithm == "-apriori") {
        apriori fiMiner(inFile);
        frequentItemsets = fiMiner.getFrequentItemsets(suppThold);
    }
    else if (algorithm == "-fptree") {
        fpTree fiMiner(inFile);
        frequentItemsets = fiMiner.getFrequentItemsets(suppThold);
    }

    cout << "Writing Results to : " << outFile << ".txt" << endl;
    // write to file
    outFile += ".txt";
    FILE* outputStream = fopen(outFile.c_str(), "w");
    for (item_set freqItemset : frequentItemsets) {
        printItemset(freqItemset, outputStream);
    }
    fclose(outputStream);

    return 0;
}