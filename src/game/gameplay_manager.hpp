/*
 University of Bologna
 First cicle degree in Computer Science
 00819 - Programmazione

 Andreea Scrob #989372
 08/13/2021

 gameplay_manager.hpp: declaration of the Game::GameplayManager class.
*/
#ifndef GAME_GAMEPLAYMANAGER_HPP
#define GAME_GAMEPLAYMANAGER_HPP
#include "menu_manager.hpp"

namespace Game {
class GameplayManager {
private:
  Data::Database &db;
  MenuManager menu_manager;

public:
  // TODO
  GameplayManager(Data::Database &, Engine::Screen &);

  MenuManager &get_menu_manager();
};
} // namespace Game
#endif