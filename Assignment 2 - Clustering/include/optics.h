#ifndef OPTICS_H
#define OPTICS_H

#include "clustering.h"

class optics : public clustering {

    public :
        optics() {}
        optics(std::vector<point> &data);
        std::unordered_map<cId, std::vector<pId>> getClusters(int minPts, double eps);

    private:
        int minPts;
        double eps;
};

#endif