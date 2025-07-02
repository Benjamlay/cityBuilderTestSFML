#include "UI/button.h"

#include <iostream>
game::ui::Button::Button(sf::Vector2f position_) {
  shape_.setSize(sf::Vector2f(50, 25));
  shape_.setFillColor(sf::Color::Black);
  shape_.setOutlineColor(sf::Color::Transparent);
  shape_.setOutlineThickness(5);
  shape_.setPosition(position_);
  shape_.setOrigin({shape_.getSize().x/2, shape_.getSize().y/2});
  //text_.setFont();
  SetZone({static_cast<sf::IntRect>(shape_.getGlobalBounds())});

  OnHoverEnter = [this] () {shape_.setScale({1.2f, 1.2f});
  };
  OnHoverExit = [this] () {shape_.setScale({1.0f, 1.0f});};
}



void game::ui::Button::Draw(sf::RenderWindow& window) {
  window.draw(shape_);
}