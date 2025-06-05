#include "npc.h"

Npc::Npc() : textures("../assets/iaTextures/") {}


Status Npc::Move(){
  std::cout << "I'm moving 2" << std::endl;
  return Status::kRunning;
}

void Npc::Setup()
{
  textures.Load("guy", textures.folder_ + "guy.png");
  root_ = std::make_unique<Action>([] () {
        std::cout << "I'm moving" << std::endl;
        return Status::kSuccess;
    });
}
void Npc::Update()
{
    root_->Tick();
}

void Npc::Draw(sf::RenderWindow& window)
{
    sf::Sprite GuySprite(textures.GetTexture("guy"));

  GuySprite.setPosition(sf::Vector2f(250, 250));
  window.draw(GuySprite);
}