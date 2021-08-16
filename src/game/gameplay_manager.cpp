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
    : db(datab), screen(scr), menu_manager(datab, scr) {}

Game::MenuManager &GameplayManager::get_menu_manager() { return menu_manager; }

inline bool can_stand(Data::MapUnit u) {
  return u == Data::MapUnit::nothing || u == Data::MapUnit::item ||
         u == Data::MapUnit::enemy;
}

void Game::GameplayManager::gravity() {
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

void Game::GameplayManager::move_left() {
  auto &player = menu_manager.get_world().player;
  auto &chunk = player.second.get_fragment()->map_chunk;
  if (player.second.move_left()) {
    auto unit =
        chunk->at(player.second.get_y()).at(player.second.get_x()).value();
    if (!can_stand(unit))
      player.second.move_right();
  }
}
void Game::GameplayManager::move_right() {
  auto &player = menu_manager.get_world().player;
  auto &chunk = player.second.get_fragment()->map_chunk;
  if (player.second.move_right()) {
    auto unit =
        chunk->at(player.second.get_y()).at(player.second.get_x()).value();
    if (!can_stand(unit))
      player.second.move_left();
  }
}
void Game::GameplayManager::move_up() {
  auto &player = menu_manager.get_world().player;
  auto &chunk = player.second.get_fragment()->map_chunk;
  int i = 3;
  while (player.second.get_y() > 0 && i > 0) {
    auto unit_above =
        chunk->at(player.second.get_y() - 1).at(player.second.get_x()).value();
    if (!can_stand(unit_above))
      break;
    menu_manager.get_world().player.second.move_up();
    i--;
  }
}
void Game::GameplayManager::move_down() {
  auto &player = menu_manager.get_world().player;
  auto &chunk = player.second.get_fragment()->map_chunk;
  auto unit_below =
      chunk->at(player.second.get_y() + 1).at(player.second.get_x()).value();
  if (!can_stand(unit_below))
    return;

  menu_manager.get_world().player.second.move_down();
}

void Game::GameplayManager::die() {
  // TODO: fill
  screen.send_event(Engine::Drawable::Event::interact);
}