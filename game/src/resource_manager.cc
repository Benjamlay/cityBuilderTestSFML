#include "resources/resource_manager.h"

#include <SFML/Graphics/Sprite.hpp>
#include <ranges>

ResourceManager::ResourceManager() : textures_("../assets/textures/") {
  textures_.GetTexture("tree");
  textures_.Load("tree", textures_.folder_ + "tree.png");
  textures_.Load("rock", textures_.folder_ + "rock.png");
}
void ResourceManager::AddTree(sf::Vector2f pos) {
  resources_.emplace_back(pos, TREE);
}
void ResourceManager::AddRock(sf::Vector2f pos) {
  resources_.emplace_back(pos, ROCK);
}
void ResourceManager::AddFlower(sf::Vector2f pos) {
  resources_.emplace_back(pos, FLOWER);
}

void ResourceManager::Update(float dt) {

}

void ResourceManager::Draw(sf::RenderWindow& window) {
  int resourceTileIndex = 0;
  sf::Sprite resourceSprite(textures_.GetTexture("empty"));

  for (auto resource : resources_) {
    if (resource.getType() != EMPTY) {
      switch (resource) {
        case ROCK:
          resourceSprite.setTexture(textures_.GetTexture("rock"));
          break;
        case TREE:
          resourceSprite.setTexture(textures_.GetTexture("tree"));
          break;
        default:
          break;
      }
      resourceSprite.setPosition(resource.GetPosition());
      window.draw(resourceSprite);
    }
    resourceTileIndex++;
  }
}

sf::Vector2f ResourceManager::NearestResource(ResourceType type, sf::Vector2f position) {
  auto t = std::views::filter(resources_, [type](Resource& resource) {return resource.getType() == type;});

  // auto s = std::ranges::sort(
  //   t,
  //   [position] (auto r) {
  //     return distance(position, r.GetPosition());
  //   }
  //   );
float distance = 10000;
  for(auto resource : t) {

  }
}


float ResourceManager::distance(sf::Vector2f a, sf::Vector2f b) {
  float dx = a.x - b.x;
  float dy = a.y - b.y;
  return std::sqrt(dx * dx + dy * dy);
}