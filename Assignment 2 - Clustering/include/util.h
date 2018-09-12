#ifndef UTIL_H
#define UTIL_H

// #include <algorithm>
// #include <functional>
// #include <numeric>

#include "point.h"

inline double distance(point &p1, point &p2) {
    // std::vector<double> diff;
    // std::transform(p1.attributes.begin(), p1.attributes.end(), 
    //     p2.attributes.begin(), diff.begin(), std::minus<double>());
    // return std::accumulate(diff.begin(), diff.end(), 0.0, std::plus<double>());
    double dist = 0.0;
    std::vector<double> &temp1 = p1.attributes;
    std::vector<double> &temp2 = p2.attributes;
    for (int i = 0; i < temp1.size(); i++) {
        double diff = temp1[i] - temp2[i];
        dist += diff * diff;
    }
    return dist;
}

#endif