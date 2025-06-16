#ifndef PATH_H
#define PATH_H
#include <SFML/System/Vector2.hpp>
#include <optional>
#include <vector>

namespace core::motion {
class Path {
  int idxPoint_ = 0;
  std::vector<sf::Vector2f> path_points_;

  public:
  bool IsDone() const;
  [[nodiscard]] bool IsValid() const;
  sf::Vector2f GetNextPoint();
  void Fill(std::vector<sf::Vector2f>& pathPoints);

  [[nodiscard]] sf::Vector2f StartPoint() const;
};
}

#endif //PATH_H
