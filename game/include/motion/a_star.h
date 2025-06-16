#ifndef A_STAR_H
#define A_STAR_H

#include <SFML/System.hpp>
#include <__msvc_filebuf.hpp>

#include "path.h"
//using namespace core::motion;

namespace motion {
  namespace Astar {

      core::motion::Path GetPath(sf::Vector2f start, sf::Vector2f end, std::vector<sf::Vector2f> walkableTiles);

  }
}

#endif //A_STAR_H
