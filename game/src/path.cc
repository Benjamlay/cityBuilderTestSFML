#include "motion/path.h"
bool core::motion::Path::IsDone() const {
  return idxPoint_ == path_points_.size();
}

sf::Vector2f core::motion::Path::GetNextPoint() {
  if (!IsDone()) {
    ++idxPoint_;
  }
  return path_points_[idxPoint_];
}

void core::motion::Path::Fill(std::vector<sf::Vector2f>& pathPoints) {
  path_points_ = pathPoints;
}

