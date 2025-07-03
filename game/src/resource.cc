#include "resources/resource.h"


sf::Vector2f Resource::GetPosition() const { return position_; }
ResourceType Resource::getType() const {return type_;}

void Resource::Draw(sf::RenderWindow &window) {

}
