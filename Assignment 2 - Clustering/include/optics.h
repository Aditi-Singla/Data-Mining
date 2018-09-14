#ifndef OPTICS_H
#define OPTICS_H

#include "io.h"
#include "clustering.h"
#include <boost/geometry.hpp>
#include <boost/geometry/index/rtree.hpp>

namespace bg = boost::geometry;
namespace bgi = boost::geometry::index;

class optics : private clustering {

    public :
        optics() {}
        optics(std::string &inFileName);
        void readData(std::string &inFile);
        void getReachability(int minPts, double maxEps);
        std::vector<cId> getClusters(int minPts, double maxEps);

    private :
        std::vector<double> reachabilityDistances;

        void writeReachabilityFile(std::string &tempFileName);

};

#endif