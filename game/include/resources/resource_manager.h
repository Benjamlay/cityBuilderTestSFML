#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <memory>
#include <vector>

class ResourceManager {

  enum ResourceType {
    kTree,
    kRock,
    kEmpty
  };
  std::vector<sf::Vector2f> resources_;

public:
  std::vector<sf::Vector2f>& GetResources(){return resources_;}
  void AddResource(sf::Vector2f resource);
  void RemoveResource(sf::Vector2f resource);
  void Update(float dt);
  void Draw(sf::RenderWindow &window);
};


#endif //RESOURCE_MANAGER_H
