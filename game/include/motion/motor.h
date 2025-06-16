#ifndef MOTOR_H
#define MOTOR_H

#include <SFML/Graphics.hpp>



namespace core::motion {

  class motor {

    sf::Vector2f position_;
    sf::Vector2f destination_ = {0.f, 0.f};
    float speed_;
    float remaining_distance_ = 0;

  public:
    sf::Clock clock_;

    void Update(float dt);
    float RemainingDistance() const;

    void SetSpeed(float speed){speed_ = speed;}
    void SetPosition(sf::Vector2f position){position_ = position;}
    void SetDestination(sf::Vector2f destination){destination_ = destination;}
    [[nodiscard]] const sf::Vector2f& GetPosition() const{return position_;}

  };
}
#endif //MOTOR_H
