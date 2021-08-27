/*
 University of Bologna
 First cicle degree in Computer Science
 00819 - Programmazione

 Andreea Scrob #989372
 08/13/2021

 menu_manager.hpp: declaration of the Game::MenuManager class.
*/

#ifndef GAME_MENUMANAGER_HPP
#define GAME_MENUMANAGER_HPP

#include "../data/database.hpp"
#include "../engine/screen.hpp"
#include "../world/world.hpp"
#include "settings_manager.hpp"

namespace Game {

class MenuManager {
public:
  MenuManager(Data::Database &, Engine::Screen &);

  SettingsManager &get_settings_manager();

  World::World &get_world();

  const Nostd::String get_message() const;

  bool change_content();
  bool is_in_game();

  void update_scoreboard();
  void set_in_game(bool);
  void set_message(const Nostd::String &);

private:
  SettingsManager settings_manager;

  Data::Database &db;
  Engine::Screen &screen;
  World::World *world = nullptr;
  Nostd::String message = "";

  bool in_game = false;
};
} // namespace Game

#endif
