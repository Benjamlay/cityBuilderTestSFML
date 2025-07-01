#ifndef NPC_H
#define NPC_H
#include <SFML/Graphics.hpp>

#include "_assets/asset_manager.h"
#include "ai/bt_action.h"
#include "ai/bt_selector.h"
#include "motion/motor.h"
#include "motion/path.h"
#include "tile_map.h"

using namespace core::ai::behaviour_tree;
using namespace core::motion;


class Npc {

  AssetManager<sf::Texture> textures;
  std::unique_ptr<Node> root_;
  sf::FloatRect hit_box_;

  motor motor_;
  Path path_;

  TileMap* tileMap_;

  static constexpr float kHungerRate = 1.0f;
  static constexpr float kMovingSpeed = 50.0f;


public:

  explicit Npc();
  void Setup(sf::Vector2f startPosition, TileMap* tileMap);
  void Update(float dt);
  void Draw(sf::RenderWindow &window);
  motor getMotor() const;
  sf::FloatRect GetHitBox();

  Status Move();
  Status IsHungry();
  Status Eat();
  Status findResource();
  Status findHome();
  Status StartChoping();
  Status ChopingTree();
  //Status Sleep();

  sf::Vector2f NearestResource(std::vector<sf::Vector2f>& collectibles);
  void SetupBehaviourTree();

  int hunger_;
  int chooping_timer_;
  bool is_eating_ = false;
  bool is_chooping = false;
  sf::Vector2f destination_;
  sf::Vector2f start_position_;

  //motion

  void SetPath(const Path& path);
};
#endif //NPC_H
