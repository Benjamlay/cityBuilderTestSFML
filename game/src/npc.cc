#include "npc.h"

Npc::Npc() : textures("../assets/iaTextures/") {}

void Npc::Setup()
{
   textures.Load("guy", textures.folder_ + "guy.png");
}

void Npc::Draw(sf::RenderWindow& window)
{
    sf::Sprite GuySprite(textures.GetTexture("guy"));

  GuySprite.setPosition(sf::Vector2f(250, 250));
  window.draw(GuySprite);
}