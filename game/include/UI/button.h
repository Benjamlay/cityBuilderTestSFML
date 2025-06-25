#ifndef BUTTON_H
#define BUTTON_H
#include <SFML/Graphics/RectangleShape.hpp>

#include "clickable.h"

namespace game::ui {

class Button : public Clickable {

  sf::RectangleShape shape_;
  //sf::Texture texture_;

  public:

  Button(sf::Vector2f position_);
  void Draw(sf::RenderWindow& window);

};
}
#endif //BUTTON_H
