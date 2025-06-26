#include "npc_manager.h"

#include "npc_factory.h"

namespace game::ai {

  void NpcManager::Add(sf::Vector2f startPosition,TileMap *tilemap) {

    CreateNpc(npcs_,startPosition, tilemap);
    // auto npc = std::make_unique<Npc>();
    //
    // npc->Setup(startPosition, tilemap);
    // npcs_.emplace_back(std::move(npc));
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