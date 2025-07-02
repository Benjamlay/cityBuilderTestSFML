#include "../include/AI/npc.h"

#include "ai/bt_sequence.h"
#include "motion/a_star.h"

Npc::Npc() : textures("../assets/iaTextures/") {}

Status Npc::Move() {

  if (motor_.GetPosition().x == destination_.x
    && motor_.GetPosition().y == destination_.y)
  {
    return Status::kSuccess;
  }
      return Status::kRunning;
}

Status Npc::Eat() {
  is_eating_ = true;
  hunger_ -= kHungerRate;

  if (hunger_ <= 0){
    is_eating_ = false;
    return Status::kSuccess;
  }

  //std::cout << "I'm eating" << std::endl;
  return Status::kRunning;
}

Status Npc::findResource() {
  destination_ = NearestResource(ressources_);

  Path path = motion::Astar::GetPath(motor_.GetPosition(), destination_,
                                     tileMap_->GetWalkables());
  if (path.IsValid()) {
    SetPath(path);
    // std::cout << "path found !" << std::endl;
    return Status::kSuccess;
  } else {
    return Status::kFailure;
  }
}

Status Npc::findHome() {
  destination_ = start_position_;
  Path path = motion::Astar::GetPath(motor_.GetPosition(), destination_, tileMap_->GetWalkables());

  if (path.IsValid()) {
    SetPath(path);
    // std::cout << "path found !" << std::endl;
    return Status::kSuccess;
  } else {
    return Status::kFailure;
  }
}

Status Npc::StartChoping() {
  // std::cout << "Chopping tree" << std::endl;
  is_choping = true;
  choping_timer_ = 100;
  return Status::kSuccess;
}
Status Npc::ChopingTree() {

  if (choping_timer_ <= 0){
    is_choping = false;
    choping_timer_ = 0;
    return Status::kSuccess;
  }
  return Status::kRunning;
}

sf::Vector2f Npc::NearestResource(std::vector<sf::Vector2f>& collectables) {

  const sf::Vector2f position = motor_.GetPosition();

  float min_distance = std::numeric_limits<float>::max();
  sf::Vector2f nearest_resource;
  auto nearest_it = collectables.end();
  for (auto it = collectables.begin(); it != collectables.end(); ++it) {
    float dx = it->x - position.x;
    float dy = it->y - position.y;
    float distance = std::sqrt(dx * dx + dy * dy);

    if (distance < min_distance) {
      min_distance = distance;
      nearest_resource = *it;
      nearest_it = it;
    }
  }
  if (nearest_it != collectables.end()) {
    collectables.erase(nearest_it);
    // TODO :1. The collectables management should not be handled within the Npc class
    //TODO :2. when the resource will be handled in a resource class, make 2 counters for each resource type to be able to quantify them
  }
  return nearest_resource;
}

Status Npc::IsHungry() {
  if (hunger_ >= 100) {
    return Status::kSuccess;
  }
  return Status::kFailure;
}

void Npc::SetupBehaviourTree(std::vector<sf::Vector2f>& collectables){

  ressources_ = collectables;

  auto feedSequence = std::make_unique<Sequence>();

  feedSequence->AddChild(std::make_unique<Action>(std::bind(&Npc::IsHungry, this)));
  feedSequence->AddChild(std::make_unique<Action>(std::bind(&Npc::findHome, this)));
  feedSequence->AddChild(std::make_unique<Action>(std::bind(&Npc::Move, this)));
  feedSequence->AddChild(std::make_unique<Action>(std::bind(&Npc::Eat, this)));

  auto workSequence = std::make_unique<Sequence>();

  workSequence->AddChild(std::make_unique<Action>(std::bind(&Npc::findResource, this)));
  workSequence->AddChild(std::make_unique<Action>(std::bind(&Npc::Move, this)));
  workSequence->AddChild(std::make_unique<Action>(std::bind(&Npc::StartChoping, this)));
  workSequence->AddChild(std::make_unique<Action>(std::bind(&Npc::ChopingTree, this)));

  auto selector = std::make_unique<Selector>();

  selector->AddChild(std::move(feedSequence));
  selector->AddChild(std::move(workSequence));

  selector->AddChild(std::make_unique<Action>([this]() {
      //std::cout << "I'm sleeping" << std::endl;
      return Status::kSuccess;
  }));

  root_ = std::move(selector);
}

void Npc::Setup(sf::Vector2f startPosition, TileMap* tileMap, std::vector<sf::Vector2f>& collectables)
{
  textures.Load("guy", textures.folder_ + "guy.png");
  textures.Load("house", textures.folder_ + "house.png");
  start_position_ = startPosition;
  hunger_ = 0;
  motor_.SetPosition(startPosition);

  motor_.SetSpeed(kMovingSpeed);

  tileMap_ = tileMap;

  SetupBehaviourTree(collectables);
}

void Npc::Update(float dt)
{
  root_->Tick();

  if (!is_eating_) {
    hunger_ += kHungerRate;
  }
  if (is_choping) {
    choping_timer_--;
  }

  if (path_.IsValid()){
    motor_.Update(dt);
    if (!path_.IsDone() && motor_.RemainingDistance() <= 0.001f) {
      motor_.SetDestination(path_.GetNextPoint());
    }
  }
}

void Npc::Draw(sf::RenderWindow& window) {
  sf::Sprite GuySprite(textures.GetTexture("guy"));
  sf::Sprite HouseSprite(textures.GetTexture("house"));
  GuySprite.setPosition(motor_.GetPosition());
  HouseSprite.setPosition(start_position_);
  window.draw(GuySprite);
  window.draw(HouseSprite);
}
motor Npc::getMotor() const { return motor_; }


sf::FloatRect Npc::GetHitBox() {
  sf::Sprite GuySprite(textures.GetTexture("guy"));
  GuySprite.setPosition(motor_.GetPosition());
  hit_box_ = GuySprite.getGlobalBounds();
  return hit_box_;
}

void Npc::SetPath(const Path& path){
  path_ = path;
  motor_.SetDestination(path_.StartPoint());
}