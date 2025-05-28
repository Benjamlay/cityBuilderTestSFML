#ifndef FUNC_H
#define FUNC_H

#include <cmath>

namespace core {

inline float Cos(Radian angle) {
  return std::cos(static_cast<float>(angle));
}
inline float Sin(Radian angle) {
  return std::sin(static_cast<float>(angle));
}
inline float Tan(Radian angle) {
  return std::tan(static_cast<float>(angle));
}

inline float ACos(Radian angle) {
  return std::acos(static_cast<float>(angle));
}

inline float ASin(Radian angle) {
  return std::asin(static_cast<float>(angle));
}

inline float ATan(Radian angle) {
  return std::atan(static_cast<float>(angle));
}


}
#endif //FUNC_H
