#include "../include/tile.h"

tile::tile(sf::Sprite sprite, sf::Texture& grass_texture_, sf::Vector2f position) : sprite_(sprite)
{
  sprite_ = sf::Sprite(grass_texture_);
  sprite_.setTexture(grass_texture_);
  sprite_.setTextureRect(sf::IntRect());
  sprite_.setPosition(position);
}


sf::Sprite& tile::getSprite()
{
  return sprite_;
}


void tile::draw(sf::RenderWindow& window)
{
  window.draw(sprite_);
}


