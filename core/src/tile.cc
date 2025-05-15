#include "tile.h"



tile::tile(sf::Texture& grass_texture_)
{
  //grass_texture_.loadFromFile("assets/grass.png");
  sprite_ = sf::Sprite(grass_texture_);
}


sf::Sprite& tile::getSprite()
{
  return *sprite_;
}

// void tile::setPosition(sf::Vector2<float> newPosition)
// {
//   setPosition(newPosition);
// }

void tile::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  target.draw(*sprite_);
}


