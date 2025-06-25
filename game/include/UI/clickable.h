#ifndef CLICKABLE_H
#define CLICKABLE_H

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <functional>

namespace game::ui {
class Clickable {

  sf::IntRect zone_;
  bool isHover_ = false;

public:
  void HandleEvent(std::optional<sf::Event> evt);
  void SetZone(sf::IntRect zone);

  std::function<void()> OnReleasedLeft;
  std::function<void()> OnReleasedRight;
  std::function<void()> OnPressedLeft;
  std::function<void()> OnPressedRight;
  std::function<void()> OnHoverEnter;
  std::function<void()> OnHoverExit;
};
}
#endif //CLICKABLE_H
