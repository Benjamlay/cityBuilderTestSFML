#include <SFML/Graphics/RenderWindow.hpp>

#include "../include/tile_map.h"
#include "maths/perlin.h"
#include <vector>




void TileMap::Draw(sf::RenderWindow &window) {
  int tileIndex = 0;

  Perlin perlin;
  std::vector<std::vector<float>> noiseMap(kHeight, std::vector<float>(kWidth));

  for (int y = 0; y < kHeight; ++y) {
    for (int x = 0; x < kWidth; ++x) {
      float fx = static_cast<float>(x) / 20.f;
      float fy = static_cast<float>(y) / 20.f;
      float value = static_cast<float>(perlin.noise(fx, fy));
      noiseMap[y][x] = value;
      Tile tileType = GetTileType(value);
    }
  }

  sf::Sprite sprite(textures.Get(0));
  // sf::Sprite sprite(default_texture_);

  for (auto element : tiles_) {
    if (element != Tile::EMPTY) {
      switch (element) {
        case Tile::GRASS:
          sprite.setTexture(textures.Get(1));
          break;
        case Tile::GRASS2:
          sprite.setTexture(textures.Get(2));
          break;
        case Tile::WATER:
          sprite.setTexture(textures.Get(3));
          break;
        default:
          break;
      }

      sprite.setPosition(ScreenPosition(tileIndex));
      window.draw(sprite);
    }

    tileIndex++;
  }
}
TileMap::Tile TileMap::GetTileType(float value)
{
  if (value < 0.3f) return Tile::WATER;
  else if (value < 0.45f) return Tile::GRASS;
  else if (value < 0.7f) return Tile::GRASS2;
  else return Tile::EMPTY;
}

sf::Vector2f TileMap::ScreenPosition(const int index) {
  float x = ceil((index % (kWidth / kPixelStep)) * kPixelStep);
  float y = ceil((index / (kWidth / kPixelStep)) * kPixelStep);

  // std::cout << "Calculated Screen Position : " << x << "." << y << "\n";

  return {x, y};
}
TileMap::TileMap() : textures("../assets/textures/") {}

// int TileMap::Index(const sf::Vector2f screenPosition){
//   return static_cast<int>(ceil(screenPosition.y / kPixelStep * kWidth)) + static_cast<int>(ceil(screenPosition.x / kPixelStep));
// }

void TileMap::Setup(){

  // grass_texture_.loadFromFile("../assets/textures/grass.png");
  // default_texture_.loadFromFile("../assets/textures/empty.png");

  textures.Load();

  tiles_.fill(Tile::GRASS2);
}
