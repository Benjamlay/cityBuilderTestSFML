#ifndef MOTOR_H
#define MOTOR_H

#include <SFML/Graphics.hpp>



namespace core::motion {

  class motor {

    sf::Vector2f position_;
    sf::Vector2f destination_;
    float speed_;

  public:
    void Update(float dt);
    void MoveTo(sf::Vector2f direction);

    void SetSpeed(float speed){speed_ = speed;}
    void SetPosition(sf::Vector2f position){position_ = position;}
    [[nodiscard]] const sf::Vector2f& GetPosition() const{return position_;}

  };
}
#endif //MOTOR_H
