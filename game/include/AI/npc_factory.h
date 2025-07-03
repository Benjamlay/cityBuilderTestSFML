#ifndef NPC_FACTORY_H
#define NPC_FACTORY_H

#include "npc.h"

namespace game::ai {

inline void CreateNpc(std::vector<std::unique_ptr<Npc>> &npcs,sf::Vector2f startPosition,
  TileMap *tilemap, ResourceManager *resource_manager, ResourceType type) {

  auto npc = std::make_unique<Npc>();

  npc->Setup(startPosition, tilemap, resource_manager, type);
  npcs.emplace_back(std::move(npc));

}
}


#endif //NPC_FACTORY_H
