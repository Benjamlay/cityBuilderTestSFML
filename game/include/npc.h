#ifndef NPC_H
#define NPC_H
#include <SFML/Graphics.hpp>

#include "_assets/asset_manager.h"
#include "ai/bt_action.h"

using namespace core::ai::behaviour_tree;
class Npc {

  AssetManager<sf::Texture> textures;
  std::unique_ptr<Node> root_;


  public:

  explicit Npc();
  void Setup();
  void Update();
  void Draw(sf::RenderWindow &window);
  Status Move();
};
#endif //NPC_H
