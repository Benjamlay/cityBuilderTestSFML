#include <SFML/Graphics/RenderWindow.hpp>

#include "../include/tile_map.h"
#include "maths/perlin.h"
#include <vector>




void TileMap::Draw(sf::RenderWindow &window) {
  int tileIndex = 0;

  //std::vector<std::vector<float>> noiseMap(kHeight, std::vector<float>(kWidth));

  //sf::Sprite sprite(textures.Get(0));
  sf::Sprite sprite(textures.GetTexture("empty"));



  //sf::Sprite sprite(default_texture_);

  for (auto element : tiles_) {
    if (element != Tile::EMPTY) {
      switch (element) {
        case Tile::GRASS:
          sprite.setTexture(textures.GetTexture("grass"));
          break;
        case Tile::GRASS2:
          sprite.setTexture(textures.GetTexture("grass2"));
          break;
        case Tile::WATER:
          sprite.setTexture(textures.GetTexture("water"));
          break;
        case Tile::SAND:
          sprite.setTexture(textures.GetTexture("tileSand"));
        default:
          break;
      }

      sprite.setPosition(ScreenPosition(tileIndex));
      window.draw(sprite);
    }

    tileIndex++;
  }
}
TileMap::Tile TileMap::GetTileType(float value) {
  if (value < 0.3f)
    return Tile::WATER;
  else if (value < 0.45f)
    return Tile::GRASS;
  else if (value < 0.7f)
    return Tile::GRASS2;
  else
    return Tile::EMPTY;
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

  //textures.Load();
  textures.Load_All();

  //tiles_.fill(Tile::GRASS);



  Perlin perlin;
  std::vector<std::vector<float>> noiseMap(kHeight/kPixelStep, std::vector<float>(kWidth/kPixelStep));

  for (int y = 0; y < kHeight/kPixelStep; ++y) {
    for (int x = 0; x < kWidth/kPixelStep; ++x) {
      float fx = x / 20.f;
      float fy = y / 20.f;
      float value = static_cast<float>(perlin.noise(fx, fy));
      noiseMap[y][x] = value;
      std::size_t index = y * kWidth/kPixelStep + x;

      if (value < 0.005f)
        tiles_[index] = Tile::WATER;
      else if (value < 0.6f)
        tiles_[index] = Tile::SAND;
      else if (value < 0.9f)
        tiles_[index] = Tile::GRASS;
      else
        tiles_[index] = Tile::GRASS2;
    }
  }

}

