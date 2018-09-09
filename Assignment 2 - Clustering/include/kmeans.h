#ifndef KMEANS_H
#define KMEANS_H

#include "clustering.h"

class kmeans : public clustering {

    public :
        kmeans() {}
        kmeans(std::string &inFileName);
        void setParams(int k);
        std::unordered_map<cId, std::vector<pId>> getClusters();

    private:
        int k;

};

#endif