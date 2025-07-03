#ifndef RESOURCE_H
#define RESOURCE_H
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System.hpp>

enum ResourceType {
  EMPTY,
  TREE,
  ROCK,
  FLOWER
};

class Resource {

  sf::Vector2f position_;
  ResourceType type_;

  public:

  Resource() = default;
  Resource(sf::Vector2f position, ResourceType type)
  : position_(position), type_(type){}
  sf::Vector2f GetPosition() const;
  ResourceType getType() const;
  void Draw(sf::RenderWindow &window);
};

#endif //RESOURCE_H
