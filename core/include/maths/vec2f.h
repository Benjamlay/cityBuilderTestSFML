
#ifndef VEC2F_H
#define VEC2F_H
#include "angle.h"
#include "func.h"

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

  [[nodiscard]] constexpr float SquareLength() const noexcept
  {
    return x * x + y * y;
  }

  [[nodiscard]] float Length() const noexcept
  {
    return std::sqrt(SquareLength());
  }

  [[nodiscard]] core::Degree angle_between(const Vec2f & v2) const noexcept
  {
    return core::Radian(std::acos((x * v2.x + y * v2.y) / (std::sqrt(x * x+y * y) * std::sqrt(v2.x * v2.x+v2.y * v2.y))));
  }

  void Rotate(const core::Degree degree)
  {
    Degree angle {std::atan2(x, y)};
    angle += degree;
    x = Length()* core::Cos(angle);
    y = Length()* core::Sin(angle);

  }
};

}


#endif //VEC2F_H
