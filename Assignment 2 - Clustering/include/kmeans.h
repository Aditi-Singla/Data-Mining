#ifndef KMEANS_H
#define KMEANS_H

#include "clustering.h"

class kmeans : public clustering {

    public :
        kmeans() {}
        kmeans(std::vector<point> &data);
        std::unordered_map<cId, std::vector<pId>> getClusters(int k);

    private:
        int k;

};

#endif