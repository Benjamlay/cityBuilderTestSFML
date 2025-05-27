//
// Created by benja on 15/05/2025.
//

#ifndef MAPGENERATOR_H
#define MAPGENERATOR_H
#include <SFML/Graphics.hpp>
#include <array>

#include "_assets/asset_manager.h"

constexpr int kWidth = 2000;
constexpr int kHeight = 2000;
constexpr int kPixelStep = 16;

class TileMap {

  enum Tile {
    EMPTY,
    GRASS,
    GRASS2,
    SAND,
    WATER

};

private:
  std::array<Tile, kWidth/kPixelStep * kHeight/kPixelStep> tiles_;
  sf::Texture grass_texture_;
  sf::Texture default_texture_;

  AssetManager<sf::Texture> textures;

  static sf::Vector2f ScreenPosition(int index);
  //static int Index(sf::Vector2f screenPosition);

public:
  explicit TileMap();
  void Setup();
  void Draw(sf::RenderWindow &window);
  Tile GetTileType(float value);

};
#endif //MAPGENERATOR_H
