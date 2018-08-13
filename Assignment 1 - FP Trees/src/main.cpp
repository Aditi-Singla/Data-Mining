#include "apriori.h"
#include "fpTree.h"

using namespace std;

int main(int argc, char **argv) {

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
    ofstream outputStream;
    outputStream.open(outFile + ".txt");
    for (item_set freqItemset : frequentItemsets) {
        // print_vec(freqItemset, outputStream);
        for (int item : freqItemset) {
            outputStream << item << ' ';
        }
        outputStream << endl;
    }
    outputStream.close();

    return 0;
}