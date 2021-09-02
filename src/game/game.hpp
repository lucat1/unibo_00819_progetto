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
#include "combat_manager.hpp"
#include "gameplay_manager.hpp"

namespace Game {

class Game {
public:
  Game();
  ~Game(); // destroyer

  int run();

private:
  Data::Database db;
  Engine::Screen screen;

  GameplayManager gameplay_manager;
  CombatManager combat_manager;

  bool running = true;
  bool loop();

  char last_key = '\0';

  int frame = 1;

  void handle_keypress();

  static void before_close(int);
};

} // namespace Game

#endif
