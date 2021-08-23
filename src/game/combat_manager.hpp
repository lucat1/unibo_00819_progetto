/*
 University of Bologna
 First cicle degree in Computer Science
 00819 - Programmazione

 Andreea Scrob #989372
 08/21/2021

 combat_manager.hpp: declaration of the Game::CombatManager class.
*/
#ifndef GAME_COMBATMANAGER_HPP
#define GAME_COMBATMANAGER_HPP

#include "../world/world.hpp"
#include "menu_manager.hpp"
namespace Game {

class CombatManager {
private:
  Nostd::Matrix<Data::Pawns::Item *>::iterator get_item();
  MenuManager &menu_manager;
  Data::MapUnit get_mapunit(World::Position);
  Nostd::Matrix<Data::Pawns::Enemy *>::iterator get_enemy(World::Position);
  Nostd::Matrix<Data::Pawns::Projectile *>::iterator
      get_projectile(World::Position);
  bool move_projectiles(Data::Pawns::Projectile, World::Position *);
  void cast_skill(Data::Pawns::Skill, World::Position);

public:
  CombatManager(MenuManager &);
  void manage_items();
  void manage_projectiles();
  void manage_enemies();
  void use_skill();
  void use_superskill();
};
} // namespace Game

#endif