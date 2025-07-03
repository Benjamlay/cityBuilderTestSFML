#include "resources/resource_manager.h"

#include <SFML/Graphics/Sprite.hpp>
#include <ranges>

ResourceManager::ResourceManager() : textures("../assets/textures/") {
  //
  textures.Load("empty", textures.folder_ + "empty.png");
  textures.Load("tree", textures.folder_ + "tree.png");
  textures.Load("rock", textures.folder_ + "rock.png");
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
  sf::Sprite resourceSprite(textures.GetTexture("empty"));

  for (auto resource : resources_) {
    if (resource.getType() != EMPTY) {
      switch (resource.getType()) {
        case ROCK:
          resourceSprite.setTexture(textures.GetTexture("rock"));
          break;
        case TREE:
          resourceSprite.setTexture(textures.GetTexture("tree"));
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

sf::Vector2f ResourceManager::NearestResource(ResourceType type, sf::Vector2f position)
{
  // auto t = std::views::filter(resources_, [type](Resource& resource) {return resource.getType() == type;});
  //
  // float MinDistance = std::numeric_limits<float>::max();
  // Resource nearest_resource;
  // for (const auto& resource : t) {
  //   float dx = resource.GetPosition().x - position.x;
  //   float dy = resource.GetPosition().y - position.y;
  //   float distance = std::sqrt(dx * dx + dy * dy);
  //
  //   if (distance < MinDistance) {
  //     MinDistance = distance;
  //     nearest_resource = resource;
  //   }
  // }
  // return nearest_resource.GetPosition();

  float minDistance = std::numeric_limits<float>::max();
  auto nearest_resource_it = resources_.end();

  for (auto it = resources_.begin(); it != resources_.end(); ++it) {
    if (it->getType() != type) {
      continue;
    }
    float dx = it->GetPosition().x - position.x;
    float dy = it->GetPosition().y - position.y;
    float distance = std::sqrt(dx * dx + dy * dy);

    if (distance < minDistance) {
      minDistance = distance;
      nearest_resource_it = it;
    }
  }
  if (nearest_resource_it != resources_.end()) {
    sf::Vector2f pos = nearest_resource_it->GetPosition();
    resources_.erase(nearest_resource_it);
    return pos;
  } else {
    throw std::runtime_error("No resource found");
  }

}


float ResourceManager::distance(sf::Vector2f a, sf::Vector2f b) {
  float dx = a.x - b.x;
  float dy = a.y - b.y;
  return std::sqrt(dx * dx + dy * dy);
}