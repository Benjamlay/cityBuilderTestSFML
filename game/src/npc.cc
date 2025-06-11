#include "npc.h"



Npc::Npc() : textures("../assets/iaTextures/") {}


Status Npc::Move(){

  std::cout << "I'm moving 2" << std::endl;
  return Status::kRunning;
}

void Npc::Setup()
{
  textures.Load("guy", textures.folder_ + "guy.png");

  motor_.SetPosition(sf::Vector2f(500, 500));

  auto selector = std::make_unique<Selector>();
  selector->AddChild(std::make_unique<Action>([this] () {
      if (hunger_ >= 100){
          std::cout << "I'm hungry, eating........" << std::endl;
          hunger_ = 0;
          return Status::kSuccess;
      }
      return Status::kFailure;
  }));
  selector->AddChild(std::make_unique<Action>([this] () {
      if (resource_available_){
          std::cout << "Resource Available, working....." << std::endl;
          return Status::kSuccess;
      }
      return Status::kFailure;
  }));
  selector->AddChild(std::make_unique<Action>([this] () {
      std::cout << "I'm sleeping" << std::endl;
      return Status::kSuccess;
  }));


  root_ = std::move(selector);
}
void Npc::Update()
{
    root_->Tick();
}

void Npc::Draw(sf::RenderWindow& window)
{
    sf::Sprite GuySprite(textures.GetTexture("guy"));

  GuySprite.setPosition(motor_.GetPosition());
  window.draw(GuySprite);
}