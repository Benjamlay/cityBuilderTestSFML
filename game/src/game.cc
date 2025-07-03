#include "../include/game.h"

#include "../include/AI/npc.h"
#include "../include/AI/npc_manager.h"
#include "../include/tile_map.h"
#include "UI/button.h"
#include "UI/clickable.h"
#include "resources/resource_manager.h"

namespace
{
  sf::RenderWindow window_;
  sf::View view = window_.getDefaultView();
  sf::View UIview = window_.getDefaultView();
  bool dragging_ = false;

  sf::Vector2i lastMousePos;
  auto tilemap_ptr_ = std::make_unique<TileMap>();

  game::ai::NpcManager npc_manager_;
  float dt;
  sf::Clock clock_;
  game::ui::Button button2({100, 170});
  sf::RectangleShape woodCounter;
  auto resource_manager = std::make_unique<ResourceManager>();

}  // namespace


static void Setup()
{
  window_.create(sf::VideoMode({1000, 1000}), "City Builder");
  int mapSeed = 4345;

  woodCounter.setSize({100, 100});
  woodCounter.setFillColor(sf::Color::Green);
  woodCounter.setPosition({100, 100});
  woodCounter.setOrigin({50, 50});
  tilemap_ptr_->Setup(mapSeed, resource_manager.get());

  npc_manager_.Add({1024, 256},tilemap_ptr_.get(), resource_manager.get(), TREE);
  npc_manager_.Add({256, 1024},tilemap_ptr_.get(), resource_manager.get(), ROCK);
  npc_manager_.Add({256, 256},tilemap_ptr_.get(), resource_manager.get(), TREE);
  npc_manager_.Add({224, 224},tilemap_ptr_.get(), resource_manager.get(), ROCK);

std::cout << "wood count: " << resource_manager->GetResources().size() << std::endl;
  tilemap_ptr_->OnReleasedRight = [] () {

    std::cout << "adding npc" << std::endl;
    sf::Vector2f spawnPoint = window_.mapPixelToCoords(sf::Mouse::getPosition(window_), view);
    npc_manager_.Add(TileMap::TilePos(static_cast<sf::Vector2i>(spawnPoint)),tilemap_ptr_.get(), resource_manager.get(), TREE);
  };

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
      //button.HandleEvent(event);
      button2.HandleEvent(event);
      tilemap_ptr_->HandleEvent(event);
    }

    window_.clear();

    npc_manager_.Update(dt);

    //update graphic

    window_.setView(view);
    tilemap_ptr_->Draw(window_);
    resource_manager->Draw(window_);
    npc_manager_.Draw(window_);

    //update UI
    window_.setView(UIview);
    //button.Draw(window_);
    button2.Draw(window_);

    //display everything
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

