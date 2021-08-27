/*
 University of Bologna
 First cicle degree in Computer Science
 00819 - Programmazione

 Andreea Scrob #989372
 08/12/2021

 settings_manager.hpp: declaration of the Game::SettingsManager class.
*/

#ifndef GAME_SETTINGSMANAGER_HPP
#define GAME_SETTINGSMANAGER_HPP

#include "../data/database.hpp"
#include "../data/setting.hpp"
#include "../nostd/vector.hpp"

namespace Game {

class SettingsManager {
public:
  SettingsManager(const Data::Database &);

  bool get_sound();

  int play_soundtrack(const char[]);
  int get_fps();

  void apply_settings();

private:
  const Data::Database &db;

  bool sound = true;

  int fps = 60;
};
} // namespace Game

#endif
