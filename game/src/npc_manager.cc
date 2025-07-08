#include "../include/AI/npc_manager.h"

#include "../include/AI/npc_factory.h"

namespace game::ai {
void NpcManager::Add(sf::Vector2f startPosition,TileMap *tilemap, ResourceManager *resource_manager, ResourceType type) {

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
}


    // namespace game::ai