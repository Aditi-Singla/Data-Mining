#include "rtree.h"

using namespace std;

void rtree::bulkLoad(vector<value> &points) {
	std::copy(points.begin(), points.end(), bgi::inserter(rt));
}

void rtree::getEpsilonNeighbourhood(vector<value> &epsilonNeighbourhood, point &startPt, double eps) {
	double x0 = startPt.get<0>();
	double x1 = startPt.get<1>();
	double x2 = startPt.get<2>();
	double x3 = startPt.get<3>();
	double x4 = startPt.get<4>();
	box boundingBox(
        getPoint(x0 - eps, x1 - eps, x2 - eps, x3 - eps, x4 - eps),
        getPoint(x0 + eps, x1 + eps, x2 + eps, x3 + eps, x4 + eps)
        );
    rt.query(
            bgi::within(boundingBox) &&
            bgi::satisfies([&](value const& v) {return bg::distance(v.first, startPt) < eps;}),
            std::back_inserter(epsilonNeighbourhood)
        );
}