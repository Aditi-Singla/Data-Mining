#include "io.h"

using namespace std;

// Input
set<item> parseLine(string &line) {
    istringstream line_stream(line);
    set<item> transaction(istream_iterator<item>{line_stream}, istream_iterator<item>());
    return transaction;
}

vector<item> parseLineVec(string &line) {
    istringstream line_stream(line);
    vector<item> transaction(istream_iterator<item>{line_stream}, istream_iterator<item>());
    return transaction;
}


// Output
void printItem(item n, std::FILE* outFile) {
    // items are positive integers
    int i = 10;
    char output_buffer[10];
    do {
        output_buffer[--i] = (n % 10) + '0';
        n /= 10;
    } while(n);
    do {
        fputc_unlocked(output_buffer[i], outFile);
    } while(++i < 10);
    fputc_unlocked(' ', outFile);
}

void printItemset(item_set itemset, std::FILE* outFile) {
    for (auto item : itemset) {
        printItem(item, outFile);
    }
    fputc_unlocked('\n', outFile);
}
