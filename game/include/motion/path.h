#ifndef PATH_H
#define PATH_H
#include <SFML/System/Vector2.hpp>
#include <vector>

namespace core::motion {
class Path {
  int idxPoint_ = 0;
  std::vector<sf::Vector2f> path_points_;

  public:
  bool IsDone() const;
  sf::Vector2f GetNextPoint();
  void Fill(std::vector<sf::Vector2f>& pathPoints);
};
}

#endif //PATH_H
