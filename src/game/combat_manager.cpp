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

Nostd::Matrix<Data::Pawns::Item *>::iterator CombatManager::overlapped_item() {
  auto &position = menu_manager.get_world().player.second;
  return position.get_fragment()->items[position.get_y()][position.get_x()];
}
Data::MapUnit CombatManager::get_mapunit(World::Position position) {
  return position.get_fragment()
      ->map_chunk->at(position.get_y())
      .at(position.get_x())
      .value();
}

void CombatManager::cast_skill(Data::Pawns::Skill skill,
                               World::Position position) {
  for (auto pair : skill.projectiles()) {
    World::Position projectile_position = position;
    switch (pair->first.first) { // x
    case -1:
      if (!projectile_position.move_left())
        continue;
      break;
    case 1:
      if (!projectile_position.move_right()) {
        menu_manager.get_world().add_chunk(1);
        projectile_position.move_right();
      }
    }

    switch (pair->first.second) { // y
    case -1:
      if (!projectile_position.move_up())
        continue;
      break;
    case 1:
      if (!projectile_position.move_down())
        continue;
    }

    if (GameplayManager::can_dig(get_mapunit(projectile_position))) {
      menu_manager.get_world().projectiles.push_back(
          {pair->second, projectile_position});
      projectile_position.get_fragment()
          ->projectiles.at(projectile_position.get_y())
          .at(projectile_position.get_x())
          .value() = &menu_manager.get_world().projectiles.back().first;
    }
  }
}

void CombatManager::manage_items() {
  auto item = overlapped_item();
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
  // TODO
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
