#include "motion/path.h"

#include <__msvc_ostream.hpp>
#include <iostream>

bool core::motion::Path::IsDone() const {
  return idxPoint_ == path_points_.size() -1;
}

sf::Vector2f core::motion::Path::GetNextPoint() {
  if (!IsValid()) {
    return {0, 0};
  }

  if (!IsDone()) {
    ++idxPoint_;
  }
  return path_points_[idxPoint_];
}

void core::motion::Path::Fill(std::vector<sf::Vector2f>& pathPoints) {
  if (!pathPoints.empty())
    path_points_ = pathPoints;
}

bool core::motion::Path::IsValid() const{
  return !path_points_.empty();
}

sf::Vector2f core::motion::Path::StartPoint() const{
  if (IsValid()) {
    return path_points_[0];
  }
  return {0, 0,};
}

