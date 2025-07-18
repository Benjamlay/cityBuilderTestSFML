#include "../../include/AI/npc.h"

#ifdef TRACY_ENABLE
#include <tracy/Tracy.hpp>
#endif // TRACY_ENABLE

#include "ai/bt_sequence.h"
#include "motion/a_star.h"

Npc::Npc() : textures("../assets/iaTextures/") {}

Status Npc::Move() {

  if (path_.IsDone())
  {
    return Status::kSuccess;
  }
      return Status::kRunning;
}

Status Npc::Eat() {
  is_eating_ = true;

  if (hunger_ <= 0){
    is_eating_ = false;
    if (type_ == FLOWER) {
      resource_manager_->flowerStock -= 2;
      return Status::kSuccess;
    }
    resource_manager_->flowerStock -= 5;
    return Status::kSuccess;
  }

  if (resource_manager_->flowerStock >= 5) {
    hunger_ -= kHungerRate * dt_ * 4;
    return Status::kRunning;
  }

  is_eating_ = false;
  return Status::kFailure;
}

Status Npc::findResource() {

  resource_search_cooldown_ = std::max(0.f, resource_search_cooldown_ - dt_);

  auto opt = resource_manager_->NearestResource(type_, motor_.GetPosition());
  if (!opt) return Status::kFailure;

  sf::Vector2f candidate = *opt;

  if (candidate == last_destination_) {
    if (resource_search_cooldown_ > 0.f)
      return Status::kFailure;
  }

  Path path = motion::Astar::GetPath(motor_.GetPosition(), candidate,
                                     tileMap_->GetWalkables());
  if (!path.IsValid()) {
    last_destination_ = candidate;
    resource_search_cooldown_ = kResourceSearchInterval;

    return Status::kFailure;
  }

  resource_manager_->ReserveResource(type_, candidate);
  destination_ = candidate;
  last_destination_ = candidate;
  SetPath(path);
  resource_search_cooldown_ = kResourceSearchInterval;
  return Status::kSuccess;
}

Status Npc::findHome() {
  destination_ = start_position_;
  Path path = motion::Astar::GetPath(motor_.GetPosition(), destination_,
                                     tileMap_->GetWalkables());

  if (path.IsValid()) {
    SetPath(path);
    return Status::kSuccess;
  } else {
    return Status::kFailure;
  }
}

Status Npc::StartChoping() {
  is_choping = true;
  choping_timer_ = 100;
  return Status::kSuccess;
}

Status Npc::ChopingTree() {

  if (choping_timer_ <= 0){
    is_choping = false;
    choping_timer_ = 0;

if (auto it = std::find_if(resource_manager_->GetResources().begin(), resource_manager_->GetResources().end(),
    [this](const Resource& r){ return r.GetPosition() == destination_; }); it != resource_manager_->GetResources().end())
  resource_manager_->GetResources().erase(it);

    if (this->getType() == TREE) {
      resource_manager_->woodStock++;
    }
    if (this->getType() == ROCK) {
      resource_manager_->rockStock++;
    }
    if (this->getType() == FLOWER) {
      resource_manager_->flowerStock++;
    }

    return Status::kSuccess;
  }
  return Status::kRunning;
}



Status Npc::IsHungry() {
  if (hunger_ >= 100) {
    return Status::kSuccess;
  }
  return Status::kFailure;
}

void Npc::SetupBehaviourTree(){

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
      return Status::kSuccess;
  }));

  root_ = std::move(selector);
}

void Npc::Setup(sf::Vector2f startPosition, const TileMap* tileMap,
                ResourceManager* resource_manager, ResourceType type)
{
#ifdef TRACY_ENABLE
  ZoneScoped;
#endif // TRACY_ENABLE

  textures.Load("treeGuy", textures.folder_ + "guy.png");
  textures.Load("rockGuy" , textures.folder_ + "StoneWorker.png");
  textures.Load("empty", textures.folder_ + "empty.png");
  textures.Load("woodHouse", textures.folder_ + "WoodHouse.png");
  textures.Load("rockHouse", textures.folder_ + "RockHouse.png");
  textures.Load("foodWorker", textures.folder_ + "FoodWorker.png");
  textures.Load("foodHouse", textures.folder_ + "FoodHouse.png");
  start_position_ = startPosition;
  hunger_ = 0;
  motor_.SetPosition(startPosition);
  resource_manager_ = resource_manager;
  type_ = type;

  motor_.SetSpeed(kMovingSpeed);

  tileMap_ = tileMap;

  SetupBehaviourTree();
}

void Npc::Update(float dt)
{
  root_->Tick();
  dt_ = dt;
  if (!is_eating_) {
    hunger_ += kHungerRate * dt_;
  }

  if (is_choping) {
    choping_timer_-= kChopingRate * dt_;
  }

  if (path_.IsValid()){
    motor_.Update(dt);
    if (!path_.IsDone() && motor_.RemainingDistance() <= 0.001f) {
      motor_.SetDestination(path_.GetNextPoint());
    }
  }
  if (hunger_ >= 180 && !is_dead) {
    is_dead = true;
  }
}

void Npc::Draw(sf::RenderWindow& window) {

  sf::Sprite GuySprite(textures.GetTexture("empty"));
  sf::Sprite HouseSprite(textures.GetTexture("empty"));
  switch (type_) {
    case ROCK:
      GuySprite.setTexture(textures.GetTexture("rockGuy"));
      HouseSprite.setTexture(textures.GetTexture("rockHouse"));
      break;
    case TREE:
      GuySprite.setTexture(textures.GetTexture("treeGuy"));
      HouseSprite.setTexture(textures.GetTexture("woodHouse"));
      break;
      case FLOWER:
      GuySprite.setTexture(textures.GetTexture("foodWorker"));
      HouseSprite.setTexture(textures.GetTexture("foodHouse"));
      break;
      case EMPTY:
      break;
      default:
      break;
  }

  if (!type_ == EMPTY) {
    GuySprite.setPosition(motor_.GetPosition());
    HouseSprite.setPosition(start_position_);
    window.draw(GuySprite);
    window.draw(HouseSprite);
  }
}

void Npc::SetPath(const Path& path){
  path_ = path;
  motor_.SetDestination(path_.StartPoint());
}