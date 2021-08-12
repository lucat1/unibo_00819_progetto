/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Andreea Scrob #989372
  08/07/2021

  game.hpp: declaration of the Game::Game class.
*/

#ifndef GAME_GAME_HPP
#define GAME_GAME_HPP
#include "../data/database.hpp"
#include "../engine/screen.hpp"
#include "../world/world.hpp"
#include "settings_manager.hpp"

namespace Game {
class Game {
private:
  Data::Database db;
  Engine::Screen screen;
  SettingsManager settings_manager;
  bool running = true;
  static void before_close(int);
  bool loop();
  void handle_keypress();
  // gameplay manager
  bool in_game = false;
  World::World *world = nullptr;
  // menu manager
  bool change_content();
  void update_scoreboard();

public:
  int run();
  Game();
};

} // namespace Game

#endif
