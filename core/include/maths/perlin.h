

#ifndef PERLIN_H
#define PERLIN_H

#include <vector>
#include <numeric>
#include <random>
#include <algorithm>
#include <cmath>

class Perlin {
public:
  Perlin();
  Perlin(unsigned int seed);

  double noise(double x, double y) const;

private:
  std::vector<int> p;

  static double fade(double t);
  static double lerp(double t, double a, double b);
  static double grad(int hash, double x, double y);
};

#endif //PERLIN_H
