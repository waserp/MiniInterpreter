#ifndef MATHFUN_H
#define MATHFUN_H


#include "CVariable.h"

float mean(std::vector<CVariable*>& parVec);
float stddev(std::vector<CVariable*>& parVec);
float minfun(std::vector<CVariable*>& parVec);
float maxfun(std::vector<CVariable*>& parVec);


#endif // MATHFUN_H
