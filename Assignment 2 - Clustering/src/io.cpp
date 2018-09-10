#include "io.h"

#include <iostream>

using namespace std;

// Input
bool parseLine(FILE* inFile, vector<double> &attributes, int size = 0) {
    register int c = fgetc_unlocked(inFile);
    if (c == EOF) {
        return false;
    }

    double n = 0, k = 1;
    int i = 0, sign = 1;
    bool done = false;

    while (c != '\n') {
        if (c > 47 && c < 58) {
            done = false;
            n = (10 * n + c - 48) * k;
            if (k != 1) {
                k *= 0.1;
            }
        }
        else if (c == '.') {
            k = 0.1;
        }
        else if (c == '-') {
            sign = -1;
        }
        else if (!done) {
            n *= sign;
            if (!size) {
                attributes.emplace_back(n);
            }
            else {
                attributes[i++] = n;
            }
            n = 0;
            done = true;
            k = 1;
            sign = 1;
        }
        c = fgetc_unlocked(inFile);
    }
    return true;
}

void readData(FILE* inFile, vector<point> &data) {
    vector<double> attributes;
    int i = 0, l = 0;
    while (parseLine(inFile, attributes, attributes.size())) {
        data.push_back(point(i++, l++, attributes));
    }
    fclose(inFile);
}


// Output
void printInt(int n, FILE* outFile) {
    int i = 10;
    char output_buffer[10];
    do {
        output_buffer[--i] = (n % 10) + '0';
        n /= 10;
    } while(n);
    do {
        fputc_unlocked(output_buffer[i], outFile);
    } while(++i < 10);
}

void printCID(cId clusterID, FILE* outFile) {
    fputc_unlocked('#', outFile);
    printInt(clusterID, outFile);
    fputc_unlocked('\n', outFile);
}

void printPID(pId pointID, int lineNo, FILE* outFile) {
    printInt(pointID, outFile);
    fputc_unlocked(' ', outFile);
    printInt(lineNo, outFile);
    fputc_unlocked('\n', outFile);
}

void printCluster(cId clusterID, std::vector<pId> &pointIDs, std::FILE* outFile) {
    printCID(clusterID, outFile);
    for (auto pointID : pointIDs) {
        printPID(pointID, pointID, outFile);
    }
}
