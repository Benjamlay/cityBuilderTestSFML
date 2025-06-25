#include "../include/game.h"

#include "../include/tile_map.h"
#include "UI/button.h"
#include "UI/clickable.h"
#include "npc.h"
#include "npc_manager.h"

namespace
{
  sf::RenderWindow window_;
  sf::View view = window_.getDefaultView();
  sf::View UIview = window_.getDefaultView();
  bool dragging_ = false;

  sf::Vector2i lastMousePos;
  TileMap tilemap_;
  //Npc npc;
  game::ai::NpcManager npc_manager_;
  float dt;
  sf::Clock clock_;
  game::ui::Button button({100, 100});
  game::ui::Button button2({100, 240});

}  // namespace


static void Setup()
{
  window_.create(sf::VideoMode({1000, 1000}), "City Builder");

  int mapSeed = 4345;
  tilemap_.Setup(mapSeed);
  //npc.Setup(&tilemap_);
  npc_manager_.Add(&tilemap_);
  //npc_manager_.Add(&tilemap_);



  dt = 0.f;
}

void game::run()
{
  Setup();

  while (window_.isOpen())
  {
    dt = clock_.restart().asSeconds();
    while (const std::optional event = window_.pollEvent()) {
      HandleEvents(event);
      //clickable_.HandleEvent(event);
      button.HandleEvent(event);
      button2.HandleEvent(event);
    }

    window_.clear();

    npc_manager_.Update(dt);

    //update graphic
    window_.setView(view);
    tilemap_.Draw(window_);
    npc_manager_.Draw(window_);

    window_.setView(UIview);
    button.Draw(window_);
    button2.Draw(window_);
    window_.display();
  }
}

void game::HandleEvents(std::optional<sf::Event> event) {

    if (event->is<sf::Event::Closed>()) {
      window_.close();
    }

    if (const auto mouseClick = event->getIf<sf::Event::MouseButtonPressed>()) {
      if (mouseClick->button == sf::Mouse::Button::Left) {
        dragging_ = true;
        lastMousePos = sf::Mouse::getPosition(window_);
      }
    }
    if (const auto mouseClick = event->getIf<sf::Event::MouseButtonReleased>()) {
      if (mouseClick->button == sf::Mouse::Button::Left) {
        dragging_ = false;
      }
    }
    if (event->is<sf::Event::MouseMoved>() && dragging_) {
      sf::Vector2i currentMousePos = sf::Mouse::getPosition(window_);
      sf::Vector2f delta = window_.mapPixelToCoords(lastMousePos) - window_.mapPixelToCoords(currentMousePos);
      view.move(delta);
      lastMousePos = currentMousePos;
    }
    if (const auto wheelScrolled = event->getIf<sf::Event::MouseWheelScrolled>()) {
      if (wheelScrolled->delta > 0) {
        view.zoom(0.9f);
      } else {
        view.zoom(1.1f);
      }
    }
}

