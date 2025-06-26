#ifndef BUTTON_H
#define BUTTON_H
#include <SFML/Graphics/RectangleShape.hpp>

#include "clickable.h"
#include "npc_factory.h"
#include "npc_manager.h"

namespace game::ui {

class Button : public Clickable {
  sf::RectangleShape shape_;
  // sf::Texture texture_;

 public:
  Button(sf::Vector2f position_);
  void SpawnNpc(ai::NpcManager npc_manager_, auto tilemap_ptr_);
  void Draw(sf::RenderWindow& window);
};
}  // namespace game::ui
#endif //BUTTON_H
