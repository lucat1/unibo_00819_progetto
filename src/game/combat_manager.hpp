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

#include "../world/random_generator.hpp"
#include "../world/world.hpp"
#include "menu_manager.hpp"

namespace Game {
/*A CombatManager implements the combat logic, allowing items,
 projectiles and enemies to take life. It also lets the player
 cast their skills.
 */
class CombatManager {
public:
  CombatManager(MenuManager &);

  void manage_items();
  void manage_projectiles();
  void manage_enemies();
  void use_skill();
  void use_superskill();

private:
  MenuManager &menu_manager;

  World::RandomGenerator random_generator;

  // Returns the MapUnit/Item/Projectile/Enemy (or an iterator to it)
  // in the given Position.
  Data::MapUnit get_mapunit(World::Position);
  Nostd::Matrix<Data::Pawns::Item *>::iterator get_item();
  Nostd::Matrix<Data::Pawns::Projectile *>::iterator
      get_projectile(World::Position);
  Nostd::Matrix<Data::Pawns::Enemy *>::iterator get_enemy(World::Position);

  // Updates the Position of a Projectile, returning true if and only if
  // this operation was successful.
  bool move_projectile(Data::Pawns::Projectile, World::Position *);

  // Casts a new Skill starting from the given Position.
  void cast_skill(Data::Pawns::Skill, World::Position);
  void enemy_act(
      Nostd::List<Nostd::Pair<Data::Pawns::Enemy, World::Position>>::iterator);
};
} // namespace Game

#endif