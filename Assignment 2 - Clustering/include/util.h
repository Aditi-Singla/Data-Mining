#ifndef UTIL_H
#define UTIL_H

#include <algorithm>
#include <functional>
#include <numeric>

#include "point.h"

inline double distance(std::vector<double> &p1, std::vector<double> &p2) {
    double dist = 0.0;
    for (int i = 0; i < p1.size(); i++) {
        double diff = p1[i] - p2[i];
        dist += diff * diff;
    }
    return dist;
}

inline double distanceVec(std::vector<double> &p1, std::vector<double> &p2, int j) {
    double dist = 0.0;
    for (int i = 0; i < p1.size(); i++) {
        double diff = p1[i] - p2[i+j];
        dist += diff * diff;
    }
    return dist;
}

#endif