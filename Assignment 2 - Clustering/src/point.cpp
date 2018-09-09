#include "point.h"

using namespace std;

point::point(int i, std::vector<double> &a) : id(i), lineNo(i), attributes(a) {};
point::point(int i, int l, std::vector<double> &a) : id(i), lineNo(l), attributes(a) {};