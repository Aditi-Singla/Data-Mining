#ifndef POINT_H
#define POINT_H

#include <vector>

#include "boost.h"

#define MAX_DIM 5

typedef int pId;
typedef int cId;

typedef bg::model::point<double, MAX_DIM, bg::cs::cartesian> point;
typedef bg::model::box<point> box;
typedef std::pair<point, pId> value;

#endif