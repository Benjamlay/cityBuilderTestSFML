#include "../include/game.h"

#include <iostream>


#include "../include/tile_map.h"

namespace
{
  sf::RenderWindow _window;
  sf::View view = _window.getDefaultView();
   bool dragging = false;
   sf::Vector2i lastMousePos;
  TileMap tilemap_;

}  // namespace


static void Setup()
{
  _window.create(sf::VideoMode({1280, 1080}), "SFML window");

  tilemap_.Setup();
}

void game::run()
{
  Setup();

  while (_window.isOpen())
  {
    HandleEvents();

    _window.clear();

    tilemap_.Draw(_window);
    _window.setView(view);
    _window.display();

  }
}



void game::HandleEvents()
{
  while (const std::optional event = _window.pollEvent())
  {
    if (event->is<sf::Event::Closed>()) {
      _window.close();
    }


    if (const auto* mouseClick = event->getIf<sf::Event::MouseButtonPressed>()) {
      if (mouseClick->button == sf::Mouse::Button::Left)
      {
        dragging = true;
        lastMousePos = sf::Mouse::getPosition(_window);
      }
    }
      if (const auto* mouseClick = event->getIf<sf::Event::MouseButtonReleased>())
      {
        if (mouseClick->button == sf::Mouse::Button::Left)
        {
          dragging = false;
        }
      }

      if (event->is<sf::Event::MouseMoved>() && dragging)
      {
        sf::Vector2i currentMousePos = sf::Mouse::getPosition(_window);
        sf::Vector2f delta = _window.mapPixelToCoords(lastMousePos) - _window.mapPixelToCoords(currentMousePos);
        view.move(delta);
        lastMousePos = currentMousePos;
      }
    if (const auto* wheelScrolled = event->getIf<sf::Event::MouseWheelScrolled>()) {
      if (wheelScrolled->delta > 0) {
        view.zoom(0.9f);
      }
      else {
        view.zoom(1.1f);
      }
    }

  }
}
