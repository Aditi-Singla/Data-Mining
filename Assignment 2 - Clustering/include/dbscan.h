#ifndef DBSCAN_H
#define DBSCAN_H

#include <boost/geometry.hpp>
#include <boost/geometry/index/rtree.hpp>

#include "clustering.h"

namespace bg = boost::geometry;
namespace bgi = boost::geometry::index;

class dbscan : private clustering {

    public :
        dbscan() {}
        dbscan(std::string &inFileName);
        std::vector<cId> getClusters(int minPts, double eps);

        void readData(std::string &inFile);

};

#endif