#ifndef NPC_FACTORY_H
#define NPC_FACTORY_H


namespace game::ai {

inline void CreateNpc(std::vector<Npc> &npcs/*, NpcType type*/, const TileMap *tilemap) {
  npcs.emplace_back();

  npcs.back().Setup(tilemap);

}
}


#endif //NPC_FACTORY_H
