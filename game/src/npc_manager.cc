#include "npc_manager.h"

#include "npc_factory.h"

namespace game::ai {



  void NpcManager::Add(const TileMap* tilemap) {

  CreateNpc(npcs_, tilemap);
  }

  void NpcManager::Update(float dt) {
    for (auto& npc : npcs_) {
      npc.Update(dt);
    }
  }

  void NpcManager::Draw(sf::RenderWindow& window) {
    for (auto& npc : npcs_) {
      npc.Draw(window);
    }
  }


}