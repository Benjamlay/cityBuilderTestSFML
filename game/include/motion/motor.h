#ifndef MOTOR_H
#define MOTOR_H

#include <SFML/Graphics.hpp>



namespace core::motion {

  class motor {

    sf::Vector2f position_;
    sf::Vector2f destination_;
    float speed_;

  public:
    sf::Clock clock_;

    void Update(float dt);

    void SetSpeed(float speed){speed_ = speed;}
    void SetPosition(sf::Vector2f position){position_ = position;}
    void SetDestination(sf::Vector2f destination){destination_ = destination;}
    [[nodiscard]] const sf::Vector2f& GetPosition() const{return position_;}

  };
}
#endif //MOTOR_H
