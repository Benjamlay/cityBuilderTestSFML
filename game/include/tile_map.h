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
  std::vector<sf::Vector2f> collectables_;

public:
  explicit TileMap();
  void Setup();
  void Draw(sf::RenderWindow &window);
  Tile GetTileType(float value);

  std::vector<sf::Vector2f> GetWalkables() const;
  std::vector<sf::Vector2f> GetCollectables() const;

};

#endif //MAPGENERATOR_H
// inline sf::Vector2i ToGridIndex(sf::Vector2f pos, int tileSize) {
//   return sf::Vector2i(
//       static_cast<int>(std::floor(pos.x / static_cast<float>(tileSize))),
//       static_cast<int>(std::floor(pos.y / static_cast<float>(tileSize)))
//   );
// }
//
// // --- Conversion inverse : indices grille -> position centrale de la tuile---
// inline sf::Vector2f ToGridPosition(sf::Vector2i idx, int tileSize) {
//   // Retourne position centrale de la tuile (tu peux utiliser le coin haut/gauche selon ton besoin)
//   return sf::Vector2f(
//       static_cast<float>(idx.x * tileSize + tileSize / 2),
//       static_cast<float>(idx.y * tileSize + tileSize / 2)
//   );
// }