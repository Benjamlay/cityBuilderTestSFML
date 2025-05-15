//
// Created by benja on 15/05/2025.
//

#include "map_generator.h"

#include <SFML/Graphics/RenderWindow.hpp>

// map_generator::map_generator() : map()
// {
//
// }

void map_generator::generate_map(std::array<sf::Sprite, 36> map)
{
  for (int x = 0; x <= x_size; x++)
    {
    for (int y = 0; y <= y_size; y++)
    {
      int idx = x * y_size + y;
    }
  }
}
void map_generator::draw(sf::RenderWindow& window) {
  for (auto& i : map) {
    window.draw(i.getSprite());
  }
}
void map_generator::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  for (auto& i : map)
  {
    target.draw(i, states);
  }
}
std::array<tile, 36> map_generator::get_map(){
  return map;
}
