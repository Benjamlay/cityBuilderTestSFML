#ifndef BUTTON_H
#define BUTTON_H
#include <SFML/Graphics/RectangleShape.hpp>

#include "../AI/npc_factory.h"
#include "../AI/npc_manager.h"
#include "clickable.h"

namespace game::ui {

class Button : public Clickable {
  sf::RectangleShape shape_;
  // sf::Texture texture_;

 public:
  Button(sf::Vector2f position_);
  void Draw(sf::RenderWindow& window);
};
}  // namespace game::ui
#endif //BUTTON_H
