#include "../include/game.h"
#include "../include/tile_map.h"
#include "npc.h"

namespace
{
  sf::RenderWindow _window;
  sf::View view = _window.getDefaultView();
  bool dragging = false;
  sf::Vector2i lastMousePos;
  TileMap tilemap_;
  Npc npc;
  float dt;
  sf::Clock clock_;

}  // namespace


static void Setup()
{
  _window.create(sf::VideoMode({1000, 1000}), "SFML window");

  tilemap_.Setup();
  npc.Setup(&tilemap_);

  dt = 0.f;
}

void game::run()
{
  Setup();


  while (_window.isOpen())
  {
    dt = clock_.restart().asSeconds();

    HandleEvents();

    _window.clear();


    npc.Update(dt);

    //update graphic
    tilemap_.Draw(_window);
    npc.Draw(_window);
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
