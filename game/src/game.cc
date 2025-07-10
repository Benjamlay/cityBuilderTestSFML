#include "../include/game.h"

#include "../include/AI/npc.h"
#include "../include/AI/npc_manager.h"
#include "../include/tile_map.h"
#include "UI/button.h"
#include "UI/clickable.h"
#include "resources/resource_manager.h"

#ifdef TRACY_ENABLE
#include <tracy/Tracy.hpp>
#endif // TRACY_ENABLE

namespace
{
  constexpr int HouseCostInWood = 5;
  constexpr int HouseCostInRock = 5;

  sf::RenderWindow window_;
  sf::View view = window_.getDefaultView();
  sf::View UIview = window_.getDefaultView();
  bool dragging_ = false;

  sf::Vector2i lastMousePos;
  auto tilemap_ptr_ = std::make_unique<TileMap>();

  sf::Font UIfont;
  sf::Text woodText = sf::Text(UIfont, "Wood: 0");
  sf::Text rockText = sf::Text(UIfont, "Rock: 0");
  sf::Text flowerText = sf::Text(UIfont, "Flower: 0");

  game::ai::NpcManager npc_manager_;
  float dt;
  sf::Clock clock_;
  game::ui::Button button_add_tree_npc({50, 800}, "tree npc");
  game::ui::Button button_add_rock_npc({200, 800}, "rock npc");
  game::ui::Button button_add_flower_npc({350, 800}, "flower npc");

  auto resource_manager = std::make_unique<ResourceManager>();

  ResourceType npc_type = EMPTY;
}  // namespace

static void Setup()
{
  {
#ifdef TRACY_ENABLE
    ZoneNamedN(window_creation_event,"Window Creation", true);
#endif // TRACY_ENABLE
    window_.create(sf::VideoMode({1000, 1000}), "City Builder");
  }
  int mapSeed = 4345;

  {
#ifdef TRACY_ENABLE
    ZoneNamedN(load_font_event,"Load Font", true);
#endif // TRACY_ENABLE
    if (!UIfont.openFromFile("assets/fonts/BabyPlums.ttf")) {
      throw std::runtime_error("Failed to load font");
    }
  }
  tilemap_ptr_->Setup(mapSeed, resource_manager.get());

  npc_manager_.Add({1024, 256},tilemap_ptr_.get(), resource_manager.get(), TREE);
  npc_manager_.Add({256, 1024},tilemap_ptr_.get(), resource_manager.get(), ROCK);

  resource_manager->SetFlower(30);
  resource_manager->SetRock(5);
  resource_manager->SetWood(5);
  tilemap_ptr_->OnReleasedLeft = [] () {
#ifdef TRACY_ENABLE
    ZoneNamedN(right_click_event,"Right Click", true);
#endif// TRACY_ENABLE

    sf::Vector2f spawnPoint = window_.mapPixelToCoords(sf::Mouse::getPosition(window_), view);

    if (game::EnoughMoneyForHouse()) {
      if (tilemap_ptr_->IsWalkable(
              TileMap::TilePos(static_cast<sf::Vector2i>(spawnPoint)))) {
        npc_manager_.Add(
            TileMap::TilePos(static_cast<sf::Vector2i>(spawnPoint)),
            tilemap_ptr_.get(), resource_manager.get(), npc_type);

        if (!npc_type == EMPTY) {
          resource_manager->RemoveWood(HouseCostInWood);
          resource_manager->RemoveRock(HouseCostInRock);}
        npc_type = EMPTY;
        }

    }
  };

  button_add_tree_npc.OnReleasedLeft = [] () {npc_type = TREE;};
  button_add_rock_npc.OnReleasedLeft = [] () {npc_type = ROCK;};
  button_add_flower_npc.OnReleasedLeft = [] () {npc_type = FLOWER;};

  dt = 0.f;
}

void game::run()
{
  Setup();

  while (window_.isOpen())
  {
    #ifdef TRACY_ENABLE
    ZoneNamedN(game_loop_event,"Game Loop", true);
    #endif // TRACY_ENABLE
    dt = clock_.restart().asSeconds();
    {
#ifdef TRACY_ENABLE
      ZoneNamedN(event_handling_event,"Event Handling", true);
#endif // TRACY_ENABLE
      while (const std::optional event = window_.pollEvent()) {
        HandleEvents(event);
        //button.HandleEvent(event);
        button_add_tree_npc.HandleEvent(event);
        button_add_rock_npc.HandleEvent(event);
        button_add_flower_npc.HandleEvent(event);
        tilemap_ptr_->HandleEvent(event);
      }
    }

    window_.clear();

    npc_manager_.Update(dt);
    resource_manager->Update(dt);
    //update graphic

    window_.setView(view);
    tilemap_ptr_->Draw(window_);
    resource_manager->Draw(window_);
    npc_manager_.Draw(window_);

    //update UI
    window_.setView(UIview);
    button_add_tree_npc.Draw(window_);
    button_add_rock_npc.Draw(window_);
    button_add_flower_npc.Draw(window_);

    woodText.setFont(UIfont);
    woodText.setString("Wood: " + std::to_string(resource_manager->GetWoodStock()));
    woodText.setCharacterSize(44);
    woodText.setFillColor(sf::Color::White);
    woodText.setPosition({20, 20});

    rockText.setFont(UIfont);
    rockText.setString("Rock: " + std::to_string(resource_manager->GetRockStock()));
    rockText.setCharacterSize(44);
    rockText.setFillColor(sf::Color::White);
    rockText.setPosition({20, 70});

    flowerText.setFont(UIfont);
    flowerText.setString("Flower: " + std::to_string(resource_manager->GetFlowerStock()));
    flowerText.setCharacterSize(44);
    flowerText.setFillColor(sf::Color::White);
    flowerText.setPosition({20, 120});


    window_.draw(woodText);
    window_.draw(rockText);
    window_.draw(flowerText);
    //display everything

    {
#ifdef TRACY_ENABLE
      ZoneNamedN(display_event,"Display Event", true);
#endif // TRACY_ENABLE
      window_.display();
    }
    #ifdef TRACY_ENABLE
    FrameMark;
    #endif // TRACY_ENABLE

  }
}

void game::HandleEvents(std::optional<sf::Event> event) {
  if (event->is<sf::Event::Closed>()) {
    window_.close();
  }

  if (const auto mouseClick = event->getIf<sf::Event::MouseButtonPressed>()) {
    if (mouseClick->button == sf::Mouse::Button::Right) {
      dragging_ = true;
      lastMousePos = sf::Mouse::getPosition(window_);
    }
  }
  if (const auto mouseClick = event->getIf<sf::Event::MouseButtonReleased>()) {
    if (mouseClick->button == sf::Mouse::Button::Right) {
      dragging_ = false;
    }
  }
  if (event->is<sf::Event::MouseMoved>() && dragging_) {
    sf::Vector2i currentMousePos = sf::Mouse::getPosition(window_);
    sf::Vector2f delta = window_.mapPixelToCoords(lastMousePos) -
                         window_.mapPixelToCoords(currentMousePos);
    view.move(delta);
    lastMousePos = currentMousePos;
  }
  if (const auto wheelScrolled =
          event->getIf<sf::Event::MouseWheelScrolled>()) {
    if (wheelScrolled->delta > 0) {
      view.zoom(0.9f);
    } else {
      view.zoom(1.1f);
    }
  }
}
bool game::EnoughMoneyForHouse() {
  return resource_manager->GetWoodStock() >= HouseCostInWood && resource_manager->GetRockStock() >= HouseCostInRock;
}

