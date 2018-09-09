#ifndef OPTICS_H
#define OPTICS_H

#include "clustering.h"

class optics : public clustering {

    public :
        optics() {}
        optics(std::string &inFileName);
        void setParams(int minPts, double eps);
        std::unordered_map<cId, std::vector<pId>> getClusters();

    private:
        int minPts;
        double eps;
};

#endif