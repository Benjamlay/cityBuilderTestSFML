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
  void NpcManager::GetHitBox() {
    for (auto& npc : npcs_) {
      npc.GetHitBox();
    }
  }
  void NpcManager::CheckCollisions(std::vector</*trees*/sf::FloatRect>& collisions) {

    for (auto& npc : npcs_) {
      for (auto& collision : collisions) {
        npc.GetHitBox();
      }
    }
  }

  }  // namespace game::ai