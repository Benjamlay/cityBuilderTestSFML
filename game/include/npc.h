#ifndef NPC_H
#define NPC_H
#include <SFML/Graphics.hpp>

#include "_assets/asset_manager.h"
#include "ai/bt_selector.h"
#include "ai/bt_action.h"

#include "motion/motor.h"

using namespace core::ai::behaviour_tree;
using namespace core::motion;


class Npc {

  AssetManager<sf::Texture> textures;
  std::unique_ptr<Node> root_;

  motor motor_;

public:

  explicit Npc();
  void Setup();
  void Update();
  void Draw(sf::RenderWindow &window);

  Status Move();

  int hunger_ = 0;
  bool resource_available_ = true;

  bool target_reachable_ = false;

};
#endif //NPC_H
