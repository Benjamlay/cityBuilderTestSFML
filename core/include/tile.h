
#ifndef TILE_H
#define TILE_H

#include <SFML/Graphics.hpp>

class tile
{
public:

  tile(sf::Sprite sprite, sf::Texture& grass_texture_, sf::Vector2f position);
  sf::Sprite& getSprite();
  void draw(sf::RenderWindow& window);

private:
  sf::Sprite sprite_;
};

#endif //TILE_H
