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


  //std::array<tile, 36> map = {};

  for(int i = 0; i < mapGenerator.get_map().size(); i++)
  {
    mapGenerator.get_map()[i].getSprite().setTexture(grass_texture_);
  }
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
      for (int i = 0; i <= 6; i++)
      {
        for (int j = 0; j <= 6; j++)
        {
          int idx = i * 6 + j;
          mapGenerator.get_map()[idx].getSprite().setPosition({static_cast<float>(i), static_cast<float>(j)});
          _window.draw(mapGenerator.get_map().at(idx).getSprite());
        }
      }
      _window.display();

    }
}

