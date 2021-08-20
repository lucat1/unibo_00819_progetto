/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Andreea Scrob #989372
  08/13/2021

  gameplay_manager.cpp: implementation of Game::GameplayManager.
*/

#include "gameplay_manager.hpp"
using Game::GameplayManager;

GameplayManager::GameplayManager(Data::Database &datab, Engine::Screen &scr)
    : screen(scr), menu_manager(datab, scr) {}

Game::MenuManager &GameplayManager::get_menu_manager() { return menu_manager; }

inline bool GameplayManager::can_stand(Data::MapUnit u) {
  return u == Data::MapUnit::nothing || u == Data::MapUnit::item ||
         u == Data::MapUnit::enemy;
}

void GameplayManager::gravity() {
  auto &player = menu_manager.get_world().player;
  auto &chunk = player.second.get_fragment()->map_chunk;
  if ((size_t)player.second.get_y() >= Data::MapChunk::height - 1)
    die();
  else {
    auto unit_below =
        chunk->at(player.second.get_y() + 1).at(player.second.get_x()).value();
    if (can_stand(unit_below) && !player.second.move_down())
      die();
  }
}

void GameplayManager::move_left() {
  auto &player = menu_manager.get_world().player;
  auto &chunk = player.second.get_fragment()->map_chunk;
  if (player.second.move_left()) {
    auto unit =
        chunk->at(player.second.get_y()).at(player.second.get_x()).value();
    if (!can_stand(unit))
      player.second.move_right();
  }
}

void GameplayManager::move_right() {
  auto &player = menu_manager.get_world().player;
  auto &chunk = player.second.get_fragment()->map_chunk;
  if (player.second.move_right()) {
    auto unit =
        chunk->at(player.second.get_y()).at(player.second.get_x()).value();
    if (!can_stand(unit))
      player.second.move_left();
  }
}

void GameplayManager::move_up() {
  auto &player = menu_manager.get_world().player;
  auto &chunk = player.second.get_fragment()->map_chunk;
  auto unit_below =
      chunk->at(player.second.get_y() + 1).at(player.second.get_x()).value();

  if (player.second.get_y() == 0 || can_stand(unit_below))
    return;
  auto unit_above =
      chunk->at(player.second.get_y() - 1).at(player.second.get_x()).value();
  if (unit_above == Data::MapUnit::platform) {
    menu_manager.get_world().player.second.move_up();
    menu_manager.get_world().player.second.move_up();
  } else {
    int i = 3;
    while (player.second.get_y() > 0 && i > 0) {
      unit_above = chunk->at(player.second.get_y() - 1)
                       .at(player.second.get_x())
                       .value();
      if (!can_stand(unit_above))
        break;
      menu_manager.get_world().player.second.move_up();
      i--;
    }
  }
}

void GameplayManager::move_down() {
  auto &player = menu_manager.get_world().player;
  auto &chunk = player.second.get_fragment()->map_chunk;
  auto unit_below =
      chunk->at(player.second.get_y() + 1).at(player.second.get_x()).value();
  if (!can_stand(unit_below))
    return;

  menu_manager.get_world().player.second.move_down();
}

void GameplayManager::die() {
  menu_manager.set_message(Nostd::String());
  screen.send_event(Engine::Drawable::Event::interact);
}

inline bool GameplayManager::can_dig(Data::MapUnit u) {
  return can_stand(u) || u == Data::MapUnit::platform;
}

void GameplayManager::move_dig() {
  auto &player = menu_manager.get_world().player;
  auto &chunk = player.second.get_fragment()->map_chunk;
  auto unit_below =
      chunk->at(player.second.get_y() + 1).at(player.second.get_x()).value();
  if (!can_dig(unit_below))
    return;

  menu_manager.get_world().player.second.move_down();
}
Nostd::Matrix<Data::Pawns::Item *>::iterator
GameplayManager::overlapped_item() {
  auto &position = menu_manager.get_world().player.second;
  return position.get_fragment()->items[position.get_y()][position.get_x()];
}

void GameplayManager::manage_items() {
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
        items.erase(p, std::next(p));
        break;
      }
    item.value() = nullptr;
  }
}
