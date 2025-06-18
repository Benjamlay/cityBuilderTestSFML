#include "gtest/gtest.h"
#include "maths/vec2.h"
#include "maths/vec2f.h"
#include <SFML/System/Vector2.hpp>

TEST(Vec2, Empty) {
  core::Vec2f v1{1.2f, 1.3f};
  sf::Vector2f v2 = sf::Vector2f(1.2f, 1.3f);
  core::Vec2<float> v { v2 };

  sf::Vector2f v3 = static_cast<sf::Vector2f>(v);
}

TEST(Vec2f, Add)
{
  float x1 = 1, x2 = 2;
  float y1 = 3, y2 = -4;

  core::Vec2 v1{x1,x2};
  core::Vec2 v2{y1,y2};

  auto result = v1 + v2;

  static_assert(result.x == x1 + y1);
  static_assert(result.y == x2 + y2);

  EXPECT_FLOAT_EQ(result.x, x1 + y1);
  EXPECT_FLOAT_EQ(result.y, x2 + y2);
}