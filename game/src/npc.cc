#include "npc.h"



Npc::Npc() : textures("../assets/iaTextures/") {}


Status Npc::Move(){

  //std::cout << "I'm moving 2" << std::endl;
  return Status::kRunning;
}

void Npc::Setup()
{
  textures.Load("guy", textures.folder_ + "guy.png");

  motor_.SetPosition({100.0f, 100.0f});
  motor_.SetDestination({1300.0f, 1300.0f});
  motor_.SetSpeed(50);
}


void Npc::Update(float dt)
{
    //root_->Tick();
  motor_.Update(dt);
}

void Npc::Draw(sf::RenderWindow& window)
{
    sf::Sprite GuySprite(textures.GetTexture("guy"));

  GuySprite.setPosition(motor_.GetPosition());
  window.draw(GuySprite);
}