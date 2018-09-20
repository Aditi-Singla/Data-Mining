#include "rtree.h"

using namespace std;

void rtree::bulkLoad(vector<double> &points, int dimension) {
	flann::Matrix<double> data(&points[0], points.size()/dimension, dimension);
	index_.buildIndex(data);
}

void rtree::getEpsilonNeighbourhood(vector<vector<int> > &epsilonNeighbourhood, vector<double> &points, 
	int index, int dimension, double eps) {
	vector<vector<double> > distances;
	flann::Matrix<double> query(&points[index], 1, dimension);
	index_.radiusSearch(query, epsilonNeighbourhood, distances, eps*eps, flann::SearchParams(-1));
}

void rtree::getEpsilonNeighbourhood(vector<vector<int> > &epsilonNeighbourhood, vector<vector<double> > &distances, 
	vector<double> &points, int index, int dimension, double eps) {
	flann::Matrix<double> query(&points[index], 1, dimension);
	index_.radiusSearch(query, epsilonNeighbourhood, distances, eps*eps, flann::SearchParams(-1));
}

void rtree::getKNN(vector<vector<int> > &neighbourhood, vector<vector<double> > &sqDistances, 
			vector<double> &points, int index, int dimension, int numNeighbours) {
	flann::Matrix<double> query(&points[index], 1, dimension);
	index_.knnSearch(query, neighbourhood, sqDistances, numNeighbours, flann::SearchParams(-1));
}