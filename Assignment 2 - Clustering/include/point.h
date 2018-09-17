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

inline void setPoint(point &pt, std::vector<double> &attributes) {

	//TODO: Any elegant way to do this?
	if (attributes.size() == 0){
		attributes.push_back(pt.get<0>());
		attributes.push_back(pt.get<1>());
		attributes.push_back(pt.get<2>());
		attributes.push_back(pt.get<3>());
		attributes.push_back(pt.get<4>());
	}
	else{
		attributes[0] = pt.get<0>();
		attributes[1] = pt.get<1>();
		attributes[2] = pt.get<2>();
		attributes[3] = pt.get<3>();
		attributes[4] = pt.get<4>();
	}
}

inline point getPoint(std::vector<double> &attributes) {
	point pt;
	pt.set<0>(attributes[0]);
	pt.set<1>(attributes[1]);
	pt.set<2>(attributes[2]);
	pt.set<3>(attributes[3]);
	pt.set<4>(attributes[4]);
	return pt;
}

#endif