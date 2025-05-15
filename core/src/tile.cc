#include "tile.h"



tile::tile(sf::Texture& grass_texture_)
{
  *sprite_ = sf::Sprite(grass_texture_);
}


sf::Sprite& tile::getSprite()
{
  return *sprite_;
}


void tile::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  target.draw(*sprite_);
}


