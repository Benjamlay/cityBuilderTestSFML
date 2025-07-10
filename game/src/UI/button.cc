#include "UI/button.h"

#include <iostream>
game::ui::Button::Button(sf::Vector2f position_, std::string text) {

  if (!UIfont.openFromFile("assets/fonts/TothePoint.ttf")) {
    throw std::runtime_error("Failed to load font");
  }
  shape_.setSize(sf::Vector2f(120, 70));
  shape_.setFillColor(sf::Color::White);
  shape_.setOutlineColor(sf::Color::White);
  shape_.setOutlineThickness(5);
  shape_.setPosition(position_);
  shape_.setOrigin({shape_.getSize().x/2, shape_.getSize().y/2});

  text_.setString(text);
  text_.setOrigin(shape_.getOrigin());
  text_.setPosition({shape_.getPosition().x, shape_.getPosition().y});
  text_.setFillColor(sf::Color::Black);
  text_.setCharacterSize(40);
  text_.setOutlineColor(sf::Color::Blue);
  SetZone({static_cast<sf::IntRect>(shape_.getGlobalBounds())});

  OnHoverEnter = [this] () {shape_.setScale({1.2f, 1.2f});
    text_.setScale({1.2f, 1.2f});
  };
  OnHoverExit = [this] () {
    shape_.setScale({1.0f, 1.0f});text_.setScale({1.0f, 1.0f});
  };
}



void game::ui::Button::Draw(sf::RenderWindow& window) {
  window.draw(shape_);
  window.draw(text_);
}