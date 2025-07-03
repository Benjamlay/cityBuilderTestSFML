#include "../include/AI/npc_manager.h"

#include "../include/AI/npc_factory.h"

namespace game::ai {

  void NpcManager::Add(sf::Vector2f startPosition,TileMap *tilemap, ResourceManager resource_manager, ResourceType type) {

    CreateNpc(npcs_,startPosition, tilemap, resource_manager, type);
  }

  void NpcManager::Update(float dt)
{
    for (auto& npc : npcs_)
    {
      npc->Update(dt);
    }
  }

  void NpcManager::Draw(sf::RenderWindow& window) {
    for (auto& npc : npcs_) {
      npc->Draw(window);
    }
  }
  void NpcManager::GetHitBox() {
    for (auto& npc : npcs_) {
      npc->GetHitBox();
    }
  }
  void NpcManager::CheckCollisions(std::vector</*trees*/sf::FloatRect>& collisions) {

    for (auto& npc : npcs_) {
      for (auto& collision : collisions) {
        npc->GetHitBox();
      }
    }
  }

  }  // namespace game::ai