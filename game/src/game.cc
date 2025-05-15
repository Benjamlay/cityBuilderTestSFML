#include "../include/game.h"
#include "map_generator.h"
#include "tile.h"

namespace
{
    sf::RenderWindow _window;
    sf::Texture grass_texture_;
    map_generator mapGenerator;
}

static void Setup()
{

   _window.create(sf::VideoMode({800, 600}), "SFML window");
    grass_texture_.loadFromFile("assets/grass.png");


  // for(int i = 0; i < mapGenerator.get_map().size(); i++)
  // {
  //   mapGenerator.get_map()[i].getSprite().setTexture(grass_texture_);
  // }
  mapGenerator.set_texture(grass_texture_);
}

void game::run()
{
  Setup();
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

      mapGenerator.generate_map(mapGenerator.get_map(), _window);

      _window.display();
    }
}

