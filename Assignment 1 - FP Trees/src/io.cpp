#include "io.h"

using namespace std;

// reference - https://www.quora.com/What-is-the-fastest-output-method-in-C

// Input
bool parseLineVec(FILE* inFile, vector<item> &transaction) {
    register int c = fgetc_unlocked(inFile);
    if (c == EOF) {
        return false;
    }
    while (c != '\n') {
        int n = 0;
        for (; (c > 47 && c < 58); c = fgetc_unlocked(inFile)) {
            n = n * 10 + c - 48;
        }
        transaction.emplace_back(n);
        c = fgetc_unlocked(inFile);
    }
    return true;
}

bool parseLineSet(FILE* inFile, set<item> &transaction) {
    register int c = fgetc_unlocked(inFile);
    if (c == EOF) {
        return false;
    }
    while (c != '\n') {
        int n = 0;
        for (; (c > 47 && c < 58); c = fgetc_unlocked(inFile)) {
            n = n * 10 + c - 48;
        }
        transaction.insert(n);
        c = fgetc_unlocked(inFile);
    }
    return true;
}


// Output
void printItem(item &n, FILE* outFile) {
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
