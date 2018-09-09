#ifndef POINT_H
#define POINT_H

#include <vector>

typedef int pId;

class point {

    public :
        pId id;
        int lineNo;
        std::vector<double> attributes;

        point() {}
        point(int i, std::vector<double> &a);
        point(int i, int l, std::vector<double> &a);
};

#endif