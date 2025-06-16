#include "motion/motor.h"

void core::motion::motor::Update(float dt) {

  const sf::Vector2f distance = destination_ - position_;

  if (distance.length() < speed_ * dt) {
   position_ = destination_;
    return;
  }
  position_ += distance.normalized() * speed_ * dt;
}

float core::motion::motor::RemainingDistance() const{
  return remaining_distance_;
}

