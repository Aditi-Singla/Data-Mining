#ifndef UTIL_H
#define UTIL_H

#include <algorithm>
#include <functional>
#include <numeric>

#include "point.h"

inline double sqDistance(std::vector<double> &points, int off1, int off2, int dim) {
    double dist = 0.0;
    for (int i = 0; i < dim; i++) {
        double diff = points[off1*dim+i] - points[off2*dim+i];
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

struct comparePoint {
    double *reachabilityDistances;

    comparePoint(double *rd): reachabilityDistances(rd) {}

    bool operator()(const POINT_OBJECT& lhs, const POINT_OBJECT& rhs) const {
        return (reachabilityDistances[rhs] <= reachabilityDistances[lhs]);
    }
};

#endif