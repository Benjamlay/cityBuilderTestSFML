#include "UI/clickable.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

namespace game::ui {

void Clickable::HandleEvent(std::optional<sf::Event> evt, bool& was_clicked){

  const auto released = evt->getIf<sf::Event::MouseButtonReleased>();
  if (released && !was_clicked) {
    if (zone_.contains(released->position)) {
      if (released->button == sf::Mouse::Button::Left) {
        if (OnReleasedLeft) {
          OnReleasedLeft();
          was_clicked |= true;
        }
      }

      if (released->button == sf::Mouse::Button::Right) {
        if (OnReleasedRight) {
          OnReleasedRight();
          was_clicked |= true;
        }
      }
    }
  }

  const auto pressed = evt->getIf<sf::Event::MouseButtonPressed>();
  if (pressed && !was_clicked) {
    if (zone_.contains(pressed->position)) {
      if (pressed->button == sf::Mouse::Button::Left) {
        if (OnPressedLeft){ OnPressedLeft(); was_clicked |= true;}
      }

      if (pressed->button == sf::Mouse::Button::Right) {
        if (OnPressedRight){ OnPressedRight();was_clicked |= true;}
      }
    }
  }
  const auto mouseMove = evt->getIf<sf::Event::MouseMoved>();
  if (mouseMove) {
    if (zone_.contains(mouseMove->position) && !isHover_) {
      if (OnHoverEnter) OnHoverEnter();
      isHover_ = true;
    }
    if (!zone_.contains(mouseMove->position) && isHover_) {
      if (OnHoverExit) OnHoverExit();
      isHover_ = false;
    }
  }
}

void Clickable::SetZone(sf::IntRect zone) {
  zone_ = zone;
}
}
// namespace game::ui
