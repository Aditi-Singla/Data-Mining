#ifndef RTREE_H
#define RTREE_H

#include <flann/flann.h>
#include <vector>
#include "point.h"

#define MAX_LEAF_NODES_KD_TREE 64

using namespace flann;
using namespace std;

class rtree
{
	private:
		flann::Index<L2_Simple<double> > index_;

	public:
		rtree(): index_(flann::KDTreeSingleIndexParams(MAX_LEAF_NODES_KD_TREE)) {};
		void bulkLoad(vector<double> &points, int dimension);
		void getEpsilonNeighbourhood(vector<vector<int> > &epsilonNeighbourhood, vector<double> &points, 
			int index, int dimension, double eps);
};

#endif