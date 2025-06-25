#include "../include/game.h"

#include "../include/tile_map.h"
#include "UI/clickable.h"
#include "npc.h"
#include "npc_manager.h"

namespace
{
  sf::RenderWindow window_;
  sf::View view = window_.getDefaultView();
  bool dragging_ = false;

  sf::Vector2i lastMousePos;
  TileMap tilemap_;
  //Npc npc;
  game::ai::NpcManager npc_manager_;
  float dt;
  sf::Clock clock_;
  game::ui::Clickable clickable_;
  sf::RectangleShape rect_;

}  // namespace


static void Setup()
{
  window_.create(sf::VideoMode({1000, 1000}), "City Builder");

  int mapSeed = 4345;
  tilemap_.Setup(mapSeed);
  //npc.Setup(&tilemap_);
  npc_manager_.Add(&tilemap_);
  //npc_manager_.Add(&tilemap_);

  rect_.setPosition({static_cast<float>(window_.getSize().x / 2), static_cast<float>(window_.getSize().y / 2)});
  rect_.setSize({200, 200});

  clickable_.SetZone(sf::IntRect(
      {static_cast<int>(window_.getSize().x / 2), static_cast<int>(window_.getSize().y / 2)},
      {200, 200})
      );
  clickable_.OnReleasedLeft = [] () {std::cout << "Left Released" << std::endl;};
  clickable_.OnReleasedRight = [] () {std::cout << "Right Released" << std::endl;};
  clickable_.OnPressedLeft = [] () {std::cout << "Left Pressed" << std::endl;};
  clickable_.OnPressedRight = [] () {std::cout << "Right Pressed" << std::endl;};
  clickable_.OnHoverEnter = [] () {std::cout << "Hover Enter" << std::endl;};
  clickable_.OnHoverExit = [] () {std::cout << "Hover Exit" << std::endl;};


  dt = 0.f;
}

void game::run()
{
  Setup();


  while (window_.isOpen())
  {
    dt = clock_.restart().asSeconds();
    sf::Vector2f mouseWorld = window_.mapPixelToCoords(sf::Mouse::getPosition(window_));
    while (const std::optional event = window_.pollEvent()) {
      HandleEvents(event);
      clickable_.HandleEvent(event);
    }

    window_.clear();


    //npc.Update(dt);
    npc_manager_.Update(dt);

    //update graphic
    tilemap_.Draw(window_);
    //npc.Draw(_window);
    npc_manager_.Draw(window_);
    window_.draw(rect_);
    window_.setView(view);
    //std::cout << "Mouse world coords: " << mouseWorld.x << ", " << mouseWorld.y << "\n";
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

