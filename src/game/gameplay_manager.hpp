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
  Engine::Screen &screen;
  MenuManager menu_manager;

public:
  GameplayManager(Data::Database &, Engine::Screen &);
  MenuManager &get_menu_manager();

  static bool can_stand(Data::MapUnit);
  static bool can_dig(Data::MapUnit);
  void gravity();
  void move_left();
  void move_right();
  void move_up();
  void move_down();
  void die();
  void move_dig();

  Nostd::Matrix<Data::Pawns::Item *>::iterator get_item();
  void manage_items();
};

} // namespace Game

#endif
