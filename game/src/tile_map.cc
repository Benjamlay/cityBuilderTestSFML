#include <SFML/Graphics.hpp>
#include "../include/tile_map.h"
#include "maths/perlin.h"
#include <vector>

void TileMap::Draw(sf::RenderWindow &window)
{
  int tileIndex = 0;
  int resourceTileIndex = 0;

  sf::Sprite sprite(textures.GetTexture("empty"));

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

  sf::Sprite resourceSprite(textures.GetTexture("empty"));

  for (auto element : resources_) {
    if (element != resourceType::EMPTY) {
      switch (element) {
        case resourceType::ROCK:
          resourceSprite.setTexture(textures.GetTexture("rock"));
          break;
        case resourceType::TREE:
          resourceSprite.setTexture(textures.GetTexture("tree"));
          break;
        default:
           break;
      }
      resourceSprite.setPosition(ScreenPosition(resourceTileIndex));
      window.draw(resourceSprite);
    }
    resourceTileIndex++;
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

  return {x, y};
}
TileMap::TileMap() : textures("../assets/textures/") {}


void TileMap::Setup() {

  textures.Load_All();

  Perlin perlin;
  std::vector noiseMap(kHeight/kPixelStep, std::vector<float>(kWidth/kPixelStep));

  for (int y = 0; y < kHeight/kPixelStep; ++y) {
    for (int x = 0; x < kWidth/kPixelStep; ++x) {
      float fx = x / 20.f;
      float fy = y / 20.f;
      float value = static_cast<float>(perlin.noise(fx, fy));
      noiseMap[y][x] = value;
      int index = y * kWidth/kPixelStep + x;

      sf::Vector2f pos = ScreenPosition(index);

      if (value < 0.01f)
        {tiles_[index] = Tile::WATER;}
      else if (value < 0.3f)
        {tiles_[index] = Tile::SAND;}
      else if (value < 0.8f)
        {tiles_[index] = Tile::GRASS;}
      else
        {tiles_[index] = Tile::GRASS2;}

      if (value > 0.95f) {
        resources_[index] = resourceType::TREE;
        collectables_.push_back(pos);
      }
      else {
        resources_[index] = resourceType::EMPTY;
      }
      if (value > 0.2f)
      {
        walkables_.push_back(pos);
      }
    }
  }

    std::cout << walkables_.size() << std::endl;
    //std::cout << tiles_.size() << std::endl;

}
std::vector<sf::Vector2f> TileMap::GetWalkables() const { return walkables_; }
std::vector<sf::Vector2f> TileMap::GetCollectables() const { return collectables_;}


