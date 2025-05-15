//
// Created by benja on 15/05/2025.
//

#ifndef MAPGENERATOR_H
#define MAPGENERATOR_H
#include <array>
#include "tile.h"

class map_generator : public sf::Drawable
{
public:



  void generate_map(std::array<sf::Sprite, 36> map);

  void draw(sf::RenderWindow& window);
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
  std::array<tile, 36> get_map();

private:
  int x_size = 6;
  int y_size = 6;
  std::array<tile, 36> map;

};
#endif //MAPGENERATOR_H
