#include "io.h"

using namespace std;

// Input
bool parseLine(FILE* inFile, vector<double> &attributes, int &size) {
    register int c = fgetc_unlocked(inFile);
    if (c == EOF) {
        return false;
    }

    double n = 0, k = 1;
    int i = 0, sign = 1;
    bool done = false;

    while (true) {
        if (c > 47 && c < 58) {
            done = false;
            n = (10 * n + c - 48);
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
            k = (k == 1)?k:10*k;
            n *= k;
            // if (!size) {
            //     attributes.emplace_back(n);
            // }
            // else {
                attributes[i++] = n;
            // }
            n = 0;
            done = true;
            k = 1;
            sign = 1;
        }
        if (c == '\n')
            break;
        c = fgetc_unlocked(inFile);
    }
    // Set the value of size
    size = i;
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

// TODO - make it efficient
void printDouble(double n, FILE* outFile) {
    fprintf(outFile, "%f\n", n);
}

void printCID(cId clusterID, FILE* outFile) {
    fputc_unlocked('#', outFile);
    if (clusterID >= 0) {
        printInt(clusterID, outFile);
    }
    else {
        fputs_unlocked("outlier", outFile);
    }
    fputc_unlocked('\n', outFile);
}

void printPID(pId pointID, FILE* outFile) {
    printInt(pointID, outFile);
    fputc_unlocked('\n', outFile);
}

void printCluster(cId clusterID, vector<pId> &pointIDs, FILE* outFile) {
    printCID(clusterID, outFile);
    for (pId pointID : pointIDs) {
        printPID(pointID, outFile);
    }
}

void printVector(vector<double> &yValues, FILE* outFile) {
    for (int i = 0; i < yValues.size(); i++) {
        printInt(i, outFile);
        fputc_unlocked(' ', outFile);
        printDouble(i, outFile);
    }
}