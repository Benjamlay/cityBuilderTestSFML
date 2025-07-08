#ifndef NPC_MANAGER_H
#define NPC_MANAGER_H
#include <vector>

#include "npc.h"

namespace game::ai {

  class NpcManager {

    std::vector<std::unique_ptr<Npc>> npcs_;

    public:

    void Add(sf::Vector2f startPosition, TileMap *tilemap, ResourceManager* resource_manager, ResourceType type);
    void Update(float dt);
    void Draw(sf::RenderWindow &window);

  };
}

#endif //NPC_MANAGER_H
