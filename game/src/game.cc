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
  _window.create(sf::VideoMode({1280, 1280}), "SFML window");

  tilemap_.Setup();
}

void game::run()
{
  Setup();

  while (_window.isOpen())
  {
    HandleEvents();

    _window.clear();

    lastMousePos = sf::Mouse::getPosition(_window);

    for (int i = 0; i <= kHeight/kPixelStep; i++) {
      for (int j = 0; j <= kWidth/kPixelStep; j++)
      {
        sf::Vector2i index = sf::Vector2i(i+1, j+1);
        if (index == lastMousePos) {
          //hover is true
          std::cout << "hover on" << std::endl;
          //doesn't work because of the zoom dezoom thing i think
        }
      }
    }
    std::cout << lastMousePos.x << "." << lastMousePos.y << std::endl;
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
