#include "MathFun.h"
#include <cmath>
#include <limits>
#include <iostream>


float mean(std::vector<CVariable*>& parVec)
{
  if (parVec[0]->GetType()!= CVariable::eVT_floatArray) {
    return nanf("0");
  }
  std::vector<float>& FloatArray = parVec[0]->GetRawFloatArray();
  double sum = 0.0;
  for ( float val : FloatArray) {
    sum += static_cast<double>(val);
  }
  size_t cnt = FloatArray.size();
  if (cnt == 0) {
    return nanf("0");
  }
  return static_cast<float>(sum)/static_cast<float>(cnt);
}




float stddev(std::vector<CVariable*>& parVec)
{
  if (parVec[0]->GetType()!= CVariable::eVT_floatArray) {
    return nanf("0");
  }
  double meanval = static_cast<double>(mean(parVec));
  std::vector<float>& FloatArray = parVec[0]->GetRawFloatArray();
  double sum = 0.0;
  for ( float val : FloatArray) {
    sum += pow((static_cast<double>(val) - meanval),2);
  }
  double cnt = static_cast<double>(FloatArray.size());
  if (cnt < 2) {
    return nanf("0");
  }
  return static_cast<float>(sqrt(sum / (cnt - 1)));
}


float minfun(std::vector<CVariable*>& parVec)
{
  float minvalue = std::numeric_limits<float>::max();
  for (auto par : parVec) {
    if (par->GetType()!= CVariable::eVT_floatArray) {
      minvalue = std::min(minvalue, par->GetFloatValue());
    } else {
      std::vector<float>& FloatArray = par->GetRawFloatArray();
      for ( float val : FloatArray) {
        minvalue = std::min(minvalue, val);
      }
    }
  }
  return minvalue;
}

float maxfun(std::vector<CVariable*>& parVec)
{
  float maxvalue = -1 * std::numeric_limits<float>::max();
  std::cout << "maxval " << maxvalue << "\n";
  for (auto par : parVec) {
    if (par->GetType()!= CVariable::eVT_floatArray) {
      maxvalue = std::max(maxvalue, par->GetFloatValue());
      std::cout << "maxval s " << maxvalue << "\n";
    } else {
      std::vector<float>& FloatArray = par->GetRawFloatArray();
      for ( float val : FloatArray) {
        maxvalue = std::max(maxvalue, val);
      }
      std::cout << "maxval v" << maxvalue << "\n";
    }
  }
  return maxvalue;
}

