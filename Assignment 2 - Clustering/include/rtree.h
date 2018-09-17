#ifndef RTREE_H
#define RTREE_H

#include <vector>
#include "point.h"

#define RSTAR_FACTOR 30

using namespace std;

typedef bgi::rtree< value, bgi::rstar<RSTAR_FACTOR> > RTREE;

class rtree
{
	private:
		RTREE rt;

	public:
		rtree() {};
		void bulkLoad(vector<value> &points);
		void getEpsilonNeighbourhood(vector<value> &epsilonNeighbourhood, point &startPt, double eps);
};

#endif