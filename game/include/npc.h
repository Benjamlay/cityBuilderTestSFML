#ifndef NPC_H
#define NPC_H
#include <SFML/Graphics.hpp>
#include "_assets/asset_manager.h"

class Npc {

  AssetManager<sf::Texture> textures;

  public:

  explicit Npc();
  void Setup();
  void Draw(sf::RenderWindow &window);
};
#endif //NPC_H
