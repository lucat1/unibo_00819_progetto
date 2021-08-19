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
private:
  const Data::Database &db;
  int fps = 60;
  bool sound = true;

public:
  SettingsManager(const Data::Database &);
  int play_soundtrack(const char[]);
  void apply_settings();
  int get_fps();
  bool get_sound();
};
} // namespace Game
#endif