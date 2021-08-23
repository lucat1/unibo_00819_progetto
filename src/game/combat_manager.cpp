/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Andreea Scrob #989372
  08/21/2021

  combat_manager.cpp: implementation of Game::CombatManager.
*/
#include "combat_manager.hpp"
#include "gameplay_manager.hpp"
using Game::CombatManager;

CombatManager::CombatManager(MenuManager &menu_manager)
    : menu_manager(menu_manager) {}

Nostd::Matrix<Data::Pawns::Item *>::iterator CombatManager::get_item() {
  auto &position = menu_manager.get_world().player.second;
  return position.get_fragment()->items[position.get_y()][position.get_x()];
}
Data::MapUnit CombatManager::get_mapunit(World::Position position) {
  return position.get_fragment()
      ->map_chunk->at(position.get_y())
      .at(position.get_x())
      .value();
}

Nostd::Matrix<Data::Pawns::Enemy *>::iterator
CombatManager::get_enemy(World::Position position) {
  return position.get_fragment()
      ->enemies.at(position.get_y())
      .at(position.get_x());
}

Nostd::Matrix<Data::Pawns::Projectile *>::iterator
CombatManager::get_projectile(World::Position position) {
  return position.get_fragment()
      ->projectiles.at(position.get_y())
      .at(position.get_x());
}

bool CombatManager::move_projectiles(Data::Pawns::Projectile projectile,
                                     World::Position *position) {
  switch (projectile.get_x()) { // x
  case -1:
    if (!position->move_left())
      return false;
    break;
  case 1:
    if (!position->move_right()) {
      menu_manager.get_world().add_chunk(1);
      position->move_right();
    }
  }

  switch (projectile.get_y()) { // y
  case -1:
    if (!position->move_up())
      return false;
    break;
  case 1:
    if (!position->move_down())
      return false;
  }
  return true;
}

void CombatManager::cast_skill(Data::Pawns::Skill skill,
                               World::Position position) {
  for (auto projectile : skill.projectiles()) {
    World::Position projectile_position = position;
    if (move_projectiles(projectile, &projectile_position) &&
        GameplayManager::can_dig(get_mapunit(projectile_position))) {
      menu_manager.get_world().projectiles.push_back(
          {projectile, projectile_position});
      projectile_position.get_fragment()
          ->projectiles.at(projectile_position.get_y())
          .at(projectile_position.get_x())
          .value() = &menu_manager.get_world().projectiles.back().first;
    }
  }
}

void CombatManager::manage_items() {
  auto item = get_item();
  if (item.value() != nullptr) {
    auto &hero = menu_manager.get_world().player.first;
    hero.interact(*item.value());
    menu_manager.set_message(Nostd::String(hero.name())
                                 .append(" found ")
                                 .append(item.value()->name())
                                 .append("!"));
    auto &items = menu_manager.get_world().items;
    for (auto p = items.begin(); p != items.end(); p++)
      if (item.value() == &p->first) {
        item.value() = nullptr;
        items.erase(p, std::next(p));
        break;
      }
  }
}

void CombatManager::manage_projectiles() {
  auto &projectiles = menu_manager.get_world().projectiles;
  for (auto p = projectiles.begin(); p != projectiles.end();) {
    bool to_be_destroyed = p->first.is_expired();
    if (!to_be_destroyed) {
      Nostd::Matrix<Data::Pawns::Enemy *>::iterator enemy =
          get_enemy(p->second);
      if (enemy.value() != nullptr && p->first.was_casted_by_player()) {
        enemy.value()->kill();
        menu_manager.get_world().player.first.increase_mana();
        enemy.value() = nullptr;
      }
      Nostd::Matrix<Data::Pawns::Projectile *>::iterator projectile_pointer =
          get_projectile(p->second);
      projectile_pointer.value() = nullptr;
      if (move_projectiles(p->first, &p->second) &&
          GameplayManager::can_dig(get_mapunit(p->second))) {
        projectile_pointer = get_projectile(p->second);
        if (projectile_pointer.value() == nullptr)
          projectile_pointer.value() = &p->first;
        else
          to_be_destroyed = true;
      } else
        to_be_destroyed = true;
    }
    if (to_be_destroyed) {
      get_projectile(p->second).value() = nullptr;
      p = projectiles.erase(p, std::next(p));
    } else {
      p->first.count_movement();
      p++;
    }
  }
}
void CombatManager::manage_enemies() {
  // TODO
}
void CombatManager::use_skill() {
  auto &hero = menu_manager.get_world().player.first;
  // TODO
  hero.interact(hero.skill());
  menu_manager.set_message(Nostd::String(hero.name())
                               .append(" used ")
                               .append(hero.skill().name())
                               .append("."));
  cast_skill(hero.skill(), menu_manager.get_world().player.second);
}
void CombatManager::use_superskill() {
  auto &hero = menu_manager.get_world().player.first;
  if (hero.attempt_super_skill()) {
    // TODO
    hero.interact(hero.superskill());
    menu_manager.set_message(Nostd::String(hero.name())
                                 .append(" used ")
                                 .append(hero.superskill().name())
                                 .append("!"));
    cast_skill(hero.superskill(), menu_manager.get_world().player.second);
  } else
    menu_manager.set_message(Nostd::String(hero.name())
                                 .append(" lacks the mana for ")
                                 .append(hero.superskill().name())
                                 .append("..."));
}
