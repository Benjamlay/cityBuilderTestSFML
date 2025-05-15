//
// Created by benja on 15/05/2025.
//

#include "map_generator.h"

#include <SFML/Graphics/RenderWindow.hpp>

// map_generator::map_generator() : map()
// {
//
// }

void map_generator::set_texture(sf::Texture texture)
{
  for (auto i : map)
  {
    i.getSprite().setTexture(texture);
  }
}
void map_generator::generate_map(std::array<tile, 36>& map, sf::RenderWindow& window)
{
  for (int x = 0; x <= x_size; x++)
    {
    for (int y = 0; y <= y_size; y++)
    {
      int idx = x * y_size + y;


      map[idx].getSprite().setPosition({static_cast<float>(x), static_cast<float>(y)});
      window.draw(map[idx]);
    }
  }
}
void map_generator::draw(sf::RenderWindow& window) {
  for (auto& tile : map) {
    window.draw(tile.getSprite());
  }
}
void map_generator::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  for (auto& i : map)
  {
    target.draw(i, states);
  }
}
std::array<tile, 36>& map_generator::get_map(){
  return map;
}
