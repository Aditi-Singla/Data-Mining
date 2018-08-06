#include "Input.h"

using namespace std;

vector<int> parseLine(string line) {
    istringstream line_stream(line);
    vector<int> transaction(istream_iterator<int>{line_stream}, istream_iterator<int>());
    return transaction;
}