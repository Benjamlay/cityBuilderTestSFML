#include "../include/game.h"

#include <iostream>

#include "map_generator.h"
#include "tile.h"

namespace
{
  sf::RenderWindow _window;
  sf::Texture grass_texture_;
  std::vector<sf::RectangleShape> tile_map;
    sf::Time time = sf::Time::Zero;
   sf::View view = _window.getDefaultView();
   bool dragging = false;
   sf::Vector2i lastMousePos;

}  // namespace


static void Setup()
{
  _window.create(sf::VideoMode({1920, 1080}), "SFML window");

  if (!grass_texture_.loadFromFile("assets/grass.png"))
  {
    std::cout << "Failed to load grass.png" << std::endl;
  }



  for (int y = 0; y < y_size; y++)
  {
    for (int x = 0; x < x_size; x++)
    {
      sf::Vector2f pos(x * 32, y * 32);
      tile_map.emplace_back(sf::RectangleShape({0, 0}));
      tile_map.back().setSize({32, 32});
      tile_map.back().setPosition(pos);
      tile_map.back().setTexture(&grass_texture_);

      // debug
      tile_map.back().setOutlineThickness(1.0f);
      tile_map.back().setOutlineColor(sf::Color::Black);

    }
  }
}

void game::run()
{
  Setup();

  while (_window.isOpen())
  {
    HandleEvents();
    for (auto& v : tile_map)
    {
      _window.draw(v);
    }

    _window.setView(view);
    _window.display();
    _window.clear();

  }
}



void game::HandleEvents()
{
  while (const std::optional event = _window.pollEvent())
  {
    if (event->is<sf::Event::Closed>()) {
      _window.close();
    }


    else if (const auto* mouseClick = event->getIf<sf::Event::MouseButtonPressed>()) {
      if (mouseClick->button == sf::Mouse::Button::Left)
      {
        dragging = true;
        std::cout << "Left button pressed" << std::endl;
        lastMousePos = sf::Mouse::getPosition(_window);
      }

     else if (const auto* MouseClick = event->getIf<sf::Event::MouseButtonReleased>())
      {
        if (MouseClick->button == sf::Mouse::Button::Left)
        {
          dragging = false;
          std::cout << "Left button released" << std::endl;
        }
      }

      else if (event->is<sf::Event::MouseMoved>() && dragging)
      {
        sf::Vector2i currentMousePos = sf::Mouse::getPosition(_window);
        sf::Vector2f delta = _window.mapPixelToCoords(lastMousePos) - _window.mapPixelToCoords(currentMousePos);
        view.move(delta);
        lastMousePos = currentMousePos;
      }
    }
  }
}
