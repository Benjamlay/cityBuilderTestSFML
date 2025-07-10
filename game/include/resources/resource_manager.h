#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <memory>
#include <vector>
#include "_assets/asset_manager.h"
#include "resource.h"
#include <optional>




class ResourceManager {

  AssetManager<sf::Texture> textures;
  std::vector<Resource> resources_;
  std::vector<Resource> resources_visited_;

  float respawn_timer_ = 0.f;
  static constexpr float kRespawnInterval = 30.f;

public:
  ResourceManager();
  std::vector<Resource>& GetResources(){return resources_;}
  std::vector<Resource>& GetResourcesVisited(){return resources_visited_;}

  int woodStock = 0;
  int rockStock = 0;
  int flowerStock = 0;

  void AddTree(sf::Vector2f pos);
  void AddRock(sf::Vector2f pos);
  void AddFlower(sf::Vector2f pos);
  void RemoveWood(int amount);
  void RemoveRock(int amount);
  void RemoveFlower(int amount);
  void SetFlower(int amount);
  void SetWood(int amount);
  void SetRock(int amount);

  static float distance(sf::Vector2f a, sf::Vector2f b);
  std::optional<sf::Vector2f> NearestResource(ResourceType type, sf::Vector2f position);
  void ReserveResource(ResourceType type, sf::Vector2f pos);


  [[nodiscard]] int GetWoodStock() const {return woodStock;}
  [[nodiscard]] int GetRockStock() const {return rockStock;}
  [[nodiscard]] int GetFlowerStock() const {return flowerStock;}
  void Update(float dt);
  void Draw(sf::RenderWindow &window);
};


#endif //RESOURCE_MANAGER_H
