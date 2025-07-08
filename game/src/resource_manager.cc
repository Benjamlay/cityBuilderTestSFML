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
void ResourceManager::RemoveWood(int amount) {woodStock -= amount;}
void ResourceManager::RemoveRock(int amount) {rockStock -= amount;}

void ResourceManager::Update(float dt) {

  respawn_timer_ += dt;
  if (respawn_timer_ >= kRespawnInterval && !resources_visited_.empty()) {
    resources_.push_back(resources_visited_.front());
    resources_visited_.erase(resources_visited_.begin());
    respawn_timer_ = 0.f;
  }

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

std::optional<sf::Vector2f> ResourceManager::NearestResource(ResourceType type, sf::Vector2f position)
{

  float bestDist = std::numeric_limits<float>::max();
  const Resource* bestRes = nullptr;

  for (auto const& r : resources_) {
    if (r.getType() != type) continue;
    // déjà visité ?
    bool seen = std::any_of(resources_visited_.begin(), resources_visited_.end(),
      [&](auto const& v){
        return v.getType()==type && v.GetPosition()==r.GetPosition();
      });
    if (seen) continue;

    float d = std::hypot(r.GetPosition().x - position.x,
                         r.GetPosition().y - position.y);
    if (d < bestDist) {
      bestDist = d;
      bestRes = &r;
    }
  }
  if (bestRes) return bestRes->GetPosition();
  return std::nullopt;

}

void ResourceManager::ReserveResource(ResourceType type, sf::Vector2f pos) {
  auto it = std::find_if(resources_.begin(), resources_.end(),
    [&](auto const& r){ return r.getType()==type && r.GetPosition()==pos; });
  if (it != resources_.end()) {
    resources_visited_.push_back(*it);
  }
}


float ResourceManager::distance(sf::Vector2f a, sf::Vector2f b) {
  float dx = a.x - b.x;
  float dy = a.y - b.y;
  return std::sqrt(dx * dx + dy * dy);
}