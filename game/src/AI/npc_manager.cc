#include "../../include/AI/npc_manager.h"

#include "../../include/AI/npc_factory.h"

#ifdef TRACY_ENABLE
#include <tracy/Tracy.hpp>
#endif // TRACY_ENABLE

namespace game::ai {
void NpcManager::Add(sf::Vector2f startPosition,TileMap *tilemap, ResourceManager *resource_manager, ResourceType type) {
#ifdef TRACY_ENABLE
  ZoneScoped;
#endif // TRACY_ENABLE
  CreateNpc(npcs_,startPosition, tilemap, resource_manager, type);
}

void NpcManager::Update(float dt)
{
#ifdef TRACY_ENABLE
  ZoneScoped;
#endif // TRACY_ENABLE
  for (auto& npc : npcs_)
  {
    npc->Update(dt);
  }
}

void NpcManager::Draw(sf::RenderWindow& window) {
#ifdef TRACY_ENABLE
  ZoneScoped;
#endif // TRACY_ENABLE

  npcs_.erase(std::remove_if(npcs_.begin(), npcs_.end(),[](const std::unique_ptr<Npc>& npc){
        return npc->is_dead;}),npcs_.end()
  );

  for (auto& npc : npcs_) {
    npc->Draw(window);
  }
}
}


    // namespace game::ai