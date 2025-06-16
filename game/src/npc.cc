#include "npc.h"

#include "ai/bt_sequence.h"
#include "motion/a_star.h"

Npc::Npc() : textures("../assets/iaTextures/") {}


Status Npc::Move(){


  if (!target_reachable_) {
    std::cout << "Not reachable" << target_reachable_ << std::endl;
    return Status::kFailure;
  } else {
    std::cout << "I'm moving (distance = " << target_distance_ << ")" << std::endl;
    if (target_distance_ >= 0.15f) {
      // still arriving, return running
      target_distance_ -= kMovingSpeed;
      return Status::kRunning;
    } else {
      // if destination reached, return success
      return Status::kSuccess;
    }
  }
}

Status Npc::Eat(){
  // No failure, until we have food storage system
  hunger_ -= kHungerRate;
  if (hunger_ > 0) {
    return Status::kRunning;
  } else {
    return Status::kSuccess;
  }
}

void Npc::SetupBehaviourTree(){
  auto feedSequence = std::make_unique<Sequence>();

  feedSequence->AddChild(std::make_unique<Action>([this]() {
      if (hunger_ >= 100) {
          std::cout << "I'm hungry, wanna eat........" << std::endl;
          return Status::kSuccess;
      } else {
          std::cout << "I'm not hungry, thanks........" << std::endl;
          return Status::kFailure;
      }
  }));
  feedSequence->AddChild(std::make_unique<Action>(std::bind(&Npc::Move, this)));
  feedSequence->AddChild(std::make_unique<Action>(std::bind(&Npc::Eat, this)));

  auto selector = std::make_unique<Selector>();
  // Attach the sequence to the selector
  selector->AddChild(std::move(feedSequence));
  // Work sequence
  selector->AddChild(std::make_unique<Action>([this]() {
      hunger_ += kHungerRate * 5;
      if (resource_available_) {
          std::cout << "Resource Available, working....." << std::endl;
          return Status::kSuccess;
      }
      return Status::kFailure;
  }));
  // Idle sequence
  selector->AddChild(std::make_unique<Action>([this]() {
      hunger_ += kHungerRate * 5;
      std::cout << "I'm sleeping" << std::endl;
      return Status::kSuccess;
  }));

  root_ = std::move(selector);
}

void Npc::Setup(const TileMap* tileMap)
{
  textures.Load("guy", textures.folder_ + "guy.png");


  motor_.SetPosition({300, 300});
  //motor_.SetDestination({1300.0f, 1300.0f});
  motor_.SetSpeed(kMovingSpeed);


  tileMap_ = tileMap;

  SetupBehaviourTree();

  Path path = motion::Astar::GetPath(motor_.GetPosition(), {2560, 2560}, tileMap_->GetWalkables());

  SetPath(path);

}


void Npc::Update(float dt)
{
  if (path_.IsValid()){
    motor_.Update(dt);
    if (!path_.IsDone() && motor_.RemainingDistance() <= 0.001f) {
      motor_.SetDestination(path_.GetNextPoint());
    }
  }
  motor_.Update(dt);

}

void Npc::Draw(sf::RenderWindow& window)
{
  sf::Sprite GuySprite(textures.GetTexture("guy"));
  GuySprite.setPosition(motor_.GetPosition());
  window.draw(GuySprite);
  std::cout << "Guy pos : " << GuySprite.getPosition().x << ": "<< GuySprite.getPosition().y << std::endl;
  std::cout << "motor pos : " << motor_.GetPosition().x << ": "<< motor_.GetPosition().y << std::endl;
}

void Npc::SetPath(const Path& path){
  path_ = path;
  motor_.SetDestination(path_.StartPoint());
}