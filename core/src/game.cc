//
// Created by benja on 14/05/2025.
//

#include "game.h"

Game::Game()
{
   _window.create(sf::VideoMode({800, 600}), "SFML window");

    grass_texture_.loadFromFile("assets/grass.png");

}

void Game::run()
{
    sf::Sprite grass_sprite_(grass_texture_);
    while (_window.isOpen())
    {

        while (const std::optional event = _window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                _window.close();
            }
        }

        _window.clear();
        _window.draw(grass_sprite_);

        _window.display();

    }
}

