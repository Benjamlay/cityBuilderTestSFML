//
// Created by benja on 14/05/2025.
//


#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>


class Game
{
public:

    Game();
    void run();

private:
    sf::RenderWindow _window;
    sf::Texture grass_texture_;

};



#endif //GAME_H
