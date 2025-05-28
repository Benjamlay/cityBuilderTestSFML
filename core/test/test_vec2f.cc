#include "gtest/gtest.h"
#include "maths/vec2f.h"
#include "maths/angle.h"
#include "maths/const.h"

TEST(Vec2f, Empty) {
  core::Vec2f v;
  EXPECT_FLOAT_EQ(0, v.x);
  EXPECT_FLOAT_EQ(0, v.y);
}

TEST(Vec2f, Add)
{
  constexpr float x1 = 1, x2 = 2;
  constexpr float y1 = 3, y2 = -4;

  constexpr core::Vec2f v1{x1,x2};
  constexpr core::Vec2f v2{y1,y2};

  constexpr auto result = v1 + v2;

  static_assert(result.x == x1 + y1);
  static_assert(result.y == x2 + y2);

  EXPECT_FLOAT_EQ(result.x, x1 + y1);
  EXPECT_FLOAT_EQ(result.y, x2 + y2);
}

TEST(Vec2f, Sub)
{
  constexpr float x1 = 1, x2 = 2;
  constexpr float y1 = 3, y2 = -4;

  constexpr core::Vec2f v1{x1,x2};
  constexpr core::Vec2f v2{y1,y2};

  constexpr auto result = v1 - v2;

  static_assert(result.x == x1 - y1);
  static_assert(result.y == x2 - y2);

  EXPECT_FLOAT_EQ(result.x, x1 - y1);
  EXPECT_FLOAT_EQ(result.y, x2 - y2);
}

TEST(Vec2f, Multiplication)
{
  constexpr float x1 = 1, x2 = 2;
  constexpr float y1 = 3, y2 = -4;

  constexpr core::Vec2f v1{x1,x2};
  constexpr core::Vec2f v2{y1,y2};

  constexpr auto result = v1 * v2;

  static_assert(result.x == x1 * y1);
  static_assert(result.y == x2 * y2);

  EXPECT_FLOAT_EQ(result.x, x1 * y1);
  EXPECT_FLOAT_EQ(result.y, x2 * y2);
}

TEST(Vec2f, Div)
{
   constexpr float x1 = 1, x2 = 2;
   constexpr float y1 = 3, y2 = -4;

   constexpr core::Vec2f v1{x1,x2};
   constexpr core::Vec2f v2{y1,y2};

   constexpr auto result = v1 / v2;

  static_assert(result.x == x1 / y1);
  static_assert(result.y == x2 / y2);

  EXPECT_FLOAT_EQ(result.x, x1 / y1);
  EXPECT_FLOAT_EQ(result.y, x2 / y2);

}

TEST(Vec2f, DivByZero)
{
  float x1 = 0, x2 = 0;
  float y1 = 0, y2 = 0;

  core::Vec2f v1{x1,x2};
  core::Vec2f v2{y1,y2};

  auto result = v1 / v2;

  EXPECT_TRUE(std::isnan(result.x) || std::isnan(result.y) || std::isinf(result.x) || std::isinf(result.y));
}

TEST(Vec2f, Dot_product)
{
  constexpr float x1 = 1, x2 = 2;
  constexpr float y1 = 3, y2 = -4;

  constexpr core::Vec2f v1{x1,x2};
  constexpr core::Vec2f v2{y1,y2};

  //constexpr auto result = ;


  // EXPECT_FLOAT_EQ(result.x, x1 / y1);
  // EXPECT_FLOAT_EQ(result.y, x2 / y2);

}

TEST(Vec2f, angle_between) {

  constexpr float x1 = 0, x2 = 5;
  constexpr float y1 = 5, y2 = 0;

  constexpr core::Vec2f v1{x1,x2};
  constexpr core::Vec2f v2{y1,y2};

  core::Degree deg(90);
  auto result = v1.angle_between(v2);

  EXPECT_FLOAT_EQ(static_cast<float>(result), static_cast<float>(deg));

}

TEST(Vec2f, Rotate) {

  float x1 = 0, x2 = 5;
  float y1 = 5, y2 = 0;

  core::Vec2f v1{x1,x2};
  core::Vec2f v2{y1,y2};

  core::Degree deg(90);
  v1.Rotate(deg);

  EXPECT_NEAR(v1.x, v2.x, 0.1);
  EXPECT_NEAR(v1.y, v2.y, 0.1);
}




