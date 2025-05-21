//
// Created by benja on 15/05/2025.
//

#ifndef MAPGENERATOR_H
#define MAPGENERATOR_H
#include <array>

#include "tile.h"

constexpr int x_size = 30;
constexpr int y_size = 30;
constexpr int tile_count = x_size * y_size;


class map_generator
{
public:

  map_generator();

  void set_texture(sf::Texture texture);
  void generate_map(std::array<tile, 36>& map, sf::RenderWindow& window);

  //bool loadFromFile(const std::string& filename);

  // void draw(sf::RenderWindow& window);
  // void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
  std::array<int, tile_count> get_map();

private:

  std::array<int, tile_count> map;
  //std::array<tile, 36> map;

};
#endif //MAPGENERATOR_H
