
#ifndef VEC2F_H
#define VEC2F_H
#include "angle.h"

namespace core {

class Vec2f {
public:

  float x = 0.0f, y = 0.0f;

  constexpr Vec2f operator+(const Vec2f & v2) const noexcept
  {
    return {x + v2.x, y + v2.y};
  }

  constexpr Vec2f operator-(const Vec2f & v2) const noexcept
  {
    return {x - v2.x, y - v2.y};
  }

  constexpr Vec2f operator*(const Vec2f & v2) const noexcept
  {
    return {x * v2.x, y * v2.y};
  }

  constexpr Vec2f operator/(const Vec2f & v2) const noexcept
  {
    return {x / v2.x, y / v2.y};
  }

  constexpr Vec2f dot_product(const Vec2f & v2) const noexcept
  {
    return {x * v2.x + y * v2.y};
  }

  [[nodiscard]] core::Degree angle_between(const Vec2f & v2) const noexcept
  {
    return core::Radian(std::acos((x * v2.x + y * v2.y) / (std::sqrt(x * x+y * y) * std::sqrt(v2.x * v2.x+v2.y * v2.y))));
  }
};

}


#endif //VEC2F_H
