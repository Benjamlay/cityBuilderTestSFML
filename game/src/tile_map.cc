﻿#include "../include/tile_map.h"

#include <SFML/Graphics.hpp>
#include <vector>

#include "maths/perlin.h"

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

 //sf::Sprite resourceSprite(textures.GetTexture("empty"));

  // for (auto element : resources_) {
  //   if (element != resourceType::EMPTY) {
  //     switch (element) {
  //       case resourceType::ROCK:
  //         resourceSprite.setTexture(textures.GetTexture("rock"));
  //         break;
  //       case resourceType::TREE:
  //         resourceSprite.setTexture(textures.GetTexture("tree"));
  //         break;
  //       default:
  //          break;
  //     }
  //     resourceSprite.setPosition(ScreenPosition(resourceTileIndex));
  //     window.draw(resourceSprite);
  //   }
  //   resourceTileIndex++;
  // }

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

sf::Vector2f TileMap::TilePos(sf::Vector2i pos) {
  return {static_cast<float>(ceil(pos.x / kPixelStep) * kPixelStep),
          static_cast<float>(ceil(pos.y / kPixelStep) * kPixelStep)};
}
bool TileMap::IsWalkable(sf::Vector2f pos) {

  const auto& walk = GetWalkables();
  return std::find(walk.begin(), walk.end(), pos) != walk.end();
}


TileMap::TileMap() : textures("../assets/textures/") {}


void TileMap::Setup(int seed, ResourceManager *resources) {
  seed_ = seed;
  textures.Load_All();
  Perlin perlin(seed_);
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


      if (value > 0.5f && value < 0.75f) {
        //resources_[index].getType() = resourceType::ROCK;
        //collectibles_rocks_.push_back(pos);
        resources->AddRock(pos);
      }
      else if (value > 0.85f) {
       //resources_[index] = resourceType::TREE;
        //collectibles_trees_.push_back(pos);
        resources->AddTree(pos);


      }
      else {
        //resources_[index] = resourceType::EMPTY;
      }

      if (tiles_[index] != Tile::WATER)
      {
        walkables_.push_back(pos);
      }
    }
  }

  SetZone(sf::IntRect({0, 0}, sf::Vector2i(kWidth, kHeight)));
}
std::vector<sf::Vector2f> &TileMap::GetWalkables() { return walkables_; }
std::vector<sf::Vector2f> &TileMap::GetCollectablesTrees() {return collectibles_trees_;}
std::vector<sf::Vector2f> &TileMap::GetCollectablesRocks() {return collectibles_rocks_;}