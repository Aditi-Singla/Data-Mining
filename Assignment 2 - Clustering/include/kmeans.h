#ifndef KMEANS_H
#define KMEANS_H

#include "clustering.h"

class kmeans : private clustering {

    public :
        kmeans() {}
        kmeans(std::string &inFileName);
        std::vector<cId> getClusters(int k);
};

#endif