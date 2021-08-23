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

private:
  Data::Database &db;
  Engine::Screen &screen;
  World::World *world = nullptr;
  SettingsManager settings_manager;
  bool in_game = false;
  Nostd::String message = "";

public:
  MenuManager(Data::Database &, Engine::Screen &);
  bool change_content();
  void update_scoreboard();
  SettingsManager &get_settings_manager();
  bool is_in_game();
  void set_in_game(bool);
  World::World &get_world();

  const Nostd::String get_message() const;
  void set_message(const Nostd::String &);
};

} // namespace Game

#endif
