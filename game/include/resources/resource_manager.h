﻿#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <memory>
#include <vector>
#include "_assets/asset_manager.h"
#include "resource.h"



class ResourceManager {

  AssetManager<sf::Texture> textures;
  //std::vector<sf::Vector2f> resources_;
  std::vector<Resource> resources_;
  int woodStock = 0;
  int rockStock = 0;

public:
  ResourceManager();
  std::vector<Resource>& GetResources(){return resources_;}

  void AddTree(sf::Vector2f pos);
  void AddRock(sf::Vector2f pos);
  void AddFlower(sf::Vector2f pos);

  static float distance(sf::Vector2f a, sf::Vector2f b);
  sf::Vector2f NearestResource(ResourceType type, sf::Vector2f position);
  [[nodiscard]] int GetWoodStock() const {return woodStock;}
  [[nodiscard]] int GetRockStock() const {return rockStock;}
  void Update(float dt);
  void Draw(sf::RenderWindow &window);
};


#endif //RESOURCE_MANAGER_H
