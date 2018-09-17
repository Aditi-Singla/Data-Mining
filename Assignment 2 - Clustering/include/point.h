#ifndef POINT_H
#define POINT_H

#include <vector>

#include "boost.h"

#define MAX_DIM 5

using namespace std;

typedef int pId;
typedef int cId;

typedef bg::model::point<double, MAX_DIM, bg::cs::cartesian> point;
typedef bg::model::box<point> box;
typedef std::pair<point, pId> value;

inline point getPoint(vector<double> &attributes) {
	point pt;
	// for (int i = 0; i < MAX_DIM; ++i) {
	// 	pt.set<i>(attributes[i]);
	// }
	pt.set<0>(attributes[0]);
	pt.set<1>(attributes[1]);
	pt.set<2>(attributes[2]);
	pt.set<3>(attributes[3]);
	pt.set<4>(attributes[4]);
	return pt;
}

inline point getPoint(double x1, double x2, double x3, double x4, double x5) {
	point pt;
	pt.set<0>(x1);
	pt.set<1>(x2);
	pt.set<2>(x3);
	pt.set<3>(x4);
	pt.set<4>(x5);
	return pt;
}

#endif