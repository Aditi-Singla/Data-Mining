#include "io.h"

using namespace std;

// Input - TODO - modify to read doubles
bool parseLine(FILE* inFile, point &pt) {
    register int c = fgetc_unlocked(inFile);
    if (c == EOF) {
        return false;
    }

    int n = 0;
    bool done = false;

    while (c != '\n') {
        if (c > 47 && c < 58) {
            done = false;
            n = (n << 3) + (n << 1) + c - 48;
        } 
        else if (!done) {
            pt.attributes.emplace_back(n);
            n = 0;
            done = true;
        }

        c = fgetc_unlocked(inFile);
    }
    return true;
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
