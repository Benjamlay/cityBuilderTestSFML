//
// Created by benja on 14/05/2025.
//


#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>



namespace game
{
    void run();
    void HandleEvents(std::optional<sf::Event> evt);
    bool enoughMoneyForHouse();


};



#endif //GAME_H
