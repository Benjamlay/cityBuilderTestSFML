#ifndef FUNC_H
#define FUNC_H

#include <cmath>

namespace core {

float Cos(Radian angle) {
  return std::cos(static_cast<float>(angle));
}
float Sin(Radian angle) {
  return std::sin(static_cast<float>(angle));
}
float Tan(Radian angle) {
  return std::tan(static_cast<float>(angle));
}

float ACos(Radian angle) {
  return std::acos(static_cast<float>(angle));
}

float ASin(Radian angle) {
  return std::asin(static_cast<float>(angle));
}

float ATan(Radian angle) {
  return std::atan(static_cast<float>(angle));
}


}
#endif //FUNC_H
