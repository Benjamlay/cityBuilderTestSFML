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

  enum class Tile {
    EMPTY,
    GRASS,
    GRASS2,
    SAND,
    WATER

};
  enum class resourceType {
    EMPTY,
    TREE,
    ROCK
  };

  std::array<Tile, kWidth/kPixelStep * kHeight/kPixelStep> tiles_;
  std::array<resourceType, kWidth/kPixelStep * kHeight/kPixelStep> resources_;

  AssetManager<sf::Texture> textures;

  static sf::Vector2f ScreenPosition(int index);
  std::vector<sf::Vector2f> walkables_;
  std::vector<sf::Vector2f> collectibles_trees_;
  std::vector<sf::Vector2f> collectibles_rocks_;
  int seed_;

public:
  explicit TileMap();
  void Setup(int seed);
  void Draw(sf::RenderWindow &window);
  Tile GetTileType(float value);
  static sf::Vector2f TilePos(sf::Vector2i);

  std::vector<sf::Vector2f> GetWalkables();
  std::vector<sf::Vector2f> &GetCollectablesTrees();
  std::vector<sf::Vector2f> GetCollectablesRocks();

};

#endif //MAPGENERATOR_H