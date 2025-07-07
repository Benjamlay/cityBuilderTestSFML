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
void ResourceManager::RemoveWood(int amount) {
  woodStock -= amount;
}

void ResourceManager::Update(float dt) {

}

void ResourceManager::Draw(sf::RenderWindow& window) {
  int resourceTileIndex = 0;
  //int resourceVisitedIndex = 0;
  sf::Sprite resourceSprite(textures.GetTexture("empty"));
  //sf::Sprite resourceVisited(textures.GetTexture("empty"));

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

  // for (auto resource : resources_visited_) {
  //   if (resource.getType() != EMPTY) {
  //     switch (resource.getType()) {
  //       case ROCK:
  //         resourceVisited.setTexture(textures.GetTexture("rock"));
  //         break;
  //       case TREE:
  //         resourceVisited.setTexture(textures.GetTexture("tree"));
  //         break;
  //       default:
  //         break;
  //     }
  //     resourceVisited.setPosition(resource.GetPosition());
  //     window.draw(resourceVisited);
  //   }
  //   resourceVisitedIndex++;
  // }
}

sf::Vector2f ResourceManager::NearestResource(ResourceType type, sf::Vector2f position)
{
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
    resources_visited_.emplace_back(*nearest_resource_it);
    //resources_.erase(nearest_resource_it);
    return pos;
  } else {
    return sf::Vector2f(0, 0);
  }

}


float ResourceManager::distance(sf::Vector2f a, sf::Vector2f b) {
  float dx = a.x - b.x;
  float dy = a.y - b.y;
  return std::sqrt(dx * dx + dy * dy);
}