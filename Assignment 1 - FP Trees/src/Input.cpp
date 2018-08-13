#include "Input.h"

using namespace std;

set<int> parseLine(string &line) {
    istringstream line_stream(line);
    set<int> transaction(istream_iterator<int>{line_stream}, istream_iterator<int>());
    return transaction;
}

vector<int> parseLineVec(string &line) {
    istringstream line_stream(line);
    vector<int> transaction(istream_iterator<int>{line_stream}, istream_iterator<int>());
    return transaction;
}