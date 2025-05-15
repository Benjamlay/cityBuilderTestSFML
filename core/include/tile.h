//
// Created by benja on 15/05/2025.
//

#ifndef TILE_H
#define TILE_H
#include <SFML/Graphics.hpp>

class tile : public sf::Drawable
{
public:

  tile() = default;
  tile(sf::Texture& grass_texture_);
  sf::Sprite& getSprite();
  //void setPosition(sf::Vector2<float> newPosition);
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:

  std::optional<sf::Sprite> sprite_;
};

#endif //TILE_H
