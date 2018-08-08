#include "apriori.h"

using namespace std;

apriori::apriori(string &inFileName) {
    inFile = inFileName;
}

vector<item_set> apriori::getFrequentItemsets(double suppThold) {
    return freqItemsets;
}

// int firstPass(string &inFile, double suppThold, vector<item_set> &F_1) {
//     int numTransactions = 0;
//     unordered_map<item_set, int> C_0;
//     ifstream inputStream(inFile);

//     if (inputStream.is_open()) {
//         string line;
//         while (getline(inputStream, line)) {
//             vector<int> transaction = parseLine(line);
//             for (int item : transaction) {
//                 C_0[item_set{item}] += 1;
//             }
//             numTransactions += 1;
//         }

//         inputStream.close();
//     }

//     // calculate the frequent items and prune
//     for (auto it = C_0.begin(); it != C_0.end(); it++) {
//         if (it->second * 100.0 / numTransactions >= suppThold) {
//             F_1.push_back(it->first);
//         }
//     }
//     sort(F_1.begin(), F_1.end());

//     return numTransactions;
// }

// vector<item_set> freqItemsetsApriori(string &inFile, double suppThold) {

//     vector<item_set> freqItemsets;
//     int numTransactions, support;
    
//     // first pass
//     // vector<int> F_1;
//     // numTransactions = firstPass(inFile, suppThold, F_1);
//     // support = suppThold * 100.0 / numTransactions;

//     // cout << F_1.size() << ' ' << numTransactions << endl;

//     set<item_set> F_k;
//     set<item_set> C_k;


//     return freqItemsets;
// }

