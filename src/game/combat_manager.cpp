/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Andreea Scrob #989372
  08/21/2021

  combat_manager.cpp: implementation of Game::CombatManager.
*/
#include "combat_manager.hpp"
using Game::CombatManager;

CombatManager::CombatManager(MenuManager &menu_manager)
    : menu_manager(menu_manager) {}

Nostd::Matrix<Data::Pawns::Item *>::iterator CombatManager::overlapped_item() {
  auto &position = menu_manager.get_world().player.second;
  return position.get_fragment()->items[position.get_y()][position.get_x()];
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
  menu_manager.set_message(Nostd::String(hero.name())
                               .append(" used ")
                               .append(hero.skill().name())
                               .append("."));
}
void CombatManager::use_superskill() {
  auto &hero = menu_manager.get_world().player.first;
  if (hero.attempt_super_skill()) {
    // TODO
    menu_manager.set_message(Nostd::String(hero.name())
                                 .append(" used ")
                                 .append(hero.superskill().name())
                                 .append("!"));
  } else
    menu_manager.set_message(Nostd::String(hero.name())
                                 .append(" lacks the mana for ")
                                 .append(hero.superskill().name())
                                 .append("..."));
}
