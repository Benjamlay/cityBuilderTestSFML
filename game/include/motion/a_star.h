#ifndef A_STAR_H
#define A_STAR_H

#include <SFML/System.hpp>
#include <span>
#include "path.h"
//using namespace core::motion;

namespace motion {
  namespace Astar {

      core::motion::Path GetPath(sf::Vector2f start, sf::Vector2f end,
                             std::span<const sf::Vector2f> walkableTiles);

  }
}

#endif //A_STAR_H
