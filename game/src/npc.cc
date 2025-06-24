#include "npc.h"

#include "ai/bt_sequence.h"
#include "motion/a_star.h"

Npc::Npc() : textures("../assets/iaTextures/") {}


Status Npc::Move(){

  if (!target_reachable_) {
    std::cout << "Not reachable" << target_reachable_ << std::endl;
    //Si la target n'est pas accessible par l'aStar
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

Status Npc::Eat() {
  //No failure, until we have food storage system
  is_eating_ = true;
  hunger_ -= kHungerRate;

  if (hunger_ <= 0){
    //std::cout << "I'm full" << std::endl;
    is_eating_ = false;
    return Status::kSuccess;
  }

  //std::cout << "I'm eating" << std::endl;
  return Status::kRunning;


}
Status Npc::findResource() {

//TODO : change the end point to something than can evolve. NPC must be able to find is home too, or another tree.
  Path path = motion::Astar::GetPath(
      motor_.GetPosition(), NearestResource(tileMap_->GetCollectablesTrees()),
      tileMap_->GetWalkables());

  if (path.IsValid()) {
    SetPath(path);
    //std::cout << "path found !" << std::endl;
    return Status::kSuccess;
  }
  else {
    return Status::kFailure;
  }


}
Status Npc::GoToResource() {

  if (motor_.GetPosition().x == NearestResource(tileMap_->GetCollectablesTrees()).x
    && motor_.GetPosition().y == NearestResource(tileMap_->GetCollectablesTrees()).y)
  {
    //std::cout << "I'm at the resource" << std::endl;
    return Status::kSuccess;
  }
  else
    //std::cout << "going to the resource" << std::endl;
    return Status::kRunning;
}

Status Npc::ChopTree() {
  //std::cout << "Chopping tree" << std::endl;

  return Status::kSuccess;
}

sf::Vector2f Npc::NearestResource(const std::vector<sf::Vector2f>& collectables) {

  const sf::Vector2f position = motor_.GetPosition();

  float min_distance = std::numeric_limits<float>::max();
  sf::Vector2f nearest_resource;

  for (const auto& resource : collectables) {

    float dx = resource.x - position.x;
    float dy = resource.y - position.y;
    float distance = std::sqrt(dx * dx + dy * dy);

    if (distance < min_distance) {
      min_distance = distance;
      nearest_resource = resource;
    }
  }

  return nearest_resource;
}

Status Npc::IsHungry()
{
  if (hunger_ >= 100) {
    //std::cout << "I'm hungry, wanna eat........" << std::endl;
    return Status::kSuccess;
  }
  //std::cout << "I'm not hungry, thanks........" << std::endl;
  return Status::kFailure;
}

void Npc::SetupBehaviourTree(){

  auto feedSequence = std::make_unique<Sequence>();

  feedSequence->AddChild(std::make_unique<Action>(std::bind(&Npc::IsHungry, this)));
  feedSequence->AddChild(std::make_unique<Action>(std::bind(&Npc::Eat, this)));

  auto workSequence = std::make_unique<Sequence>();

  workSequence->AddChild(std::make_unique<Action>(std::bind(&Npc::findResource, this)));
  workSequence->AddChild(std::make_unique<Action>(std::bind(&Npc::GoToResource, this)));
  workSequence->AddChild(std::make_unique<Action>(std::bind(&Npc::ChopTree, this)));

  auto selector = std::make_unique<Selector>();
  // Attach the sequence to the selector

  selector->AddChild(std::move(feedSequence));
  selector->AddChild(std::move(workSequence));


  // Idle sequence
  selector->AddChild(std::make_unique<Action>([this]() {
      //hunger_ += kHungerRate * 5;
      //std::cout << "I'm sleeping" << std::endl;
      return Status::kSuccess;
  }));

  root_ = std::move(selector);
}

void Npc::Setup(const TileMap* tileMap)
{
  textures.Load("guy", textures.folder_ + "guy.png");

  hunger_ = 0;
  motor_.SetPosition({240, 240});

  motor_.SetSpeed(kMovingSpeed);

  tileMap_ = tileMap;

  SetupBehaviourTree();
}


void Npc::Update(float dt)
{
  auto status = root_->Tick();
  //std::cout << "Root tick returned: " << static_cast<int>(status) << std::endl;

  if (!is_eating_) {
    hunger_ += kHungerRate;
  }

  if (path_.IsValid()){
    motor_.Update(dt);
    if (!path_.IsDone() && motor_.RemainingDistance() <= 0.001f) {
      motor_.SetDestination(path_.GetNextPoint());
    }

  }
  //hunger_ += 50 * dt;

  //std::cout << "Hunger : " << hunger_ << std::endl;
}

void Npc::Draw(sf::RenderWindow& window) {
  sf::Sprite GuySprite(textures.GetTexture("guy"));
  GuySprite.setPosition(motor_.GetPosition());
  window.draw(GuySprite);
  // std::cout << "Guy pos : " << GuySprite.getPosition().x << ": "<<
  // GuySprite.getPosition().y << std::endl; std::cout << "motor pos : " <<
  // motor_.GetPosition().x << ": "<< motor_.GetPosition().y << std::endl;
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
  //std::cout << path_.StartPoint().x << ":" << path_.StartPoint().y << std::endl;
}