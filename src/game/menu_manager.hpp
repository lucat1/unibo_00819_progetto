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

  // Returns a reference to the settings manager
  SettingsManager &get_settings_manager();

  // Returns a reference to the world
  World::World &get_world();

  // Returns the currently displayed message
  Nostd::String get_message() const;

  // Gets called when a menu is closed.Decides what to display next
  bool change_content();
  // Returns true if the player is in the game
  bool is_in_game();

  void update_scoreboard();
  // Updates the value of in_game
  void set_in_game(bool);
  // Updates the massage showed on the display
  void set_message(const Nostd::String &);

private:
  Data::Database &db;
  Engine::Screen &screen;
  World::World *world = nullptr;
  Nostd::String message = "";

  SettingsManager settings_manager;

  bool in_game = false;
};
} // namespace Game

#endif
