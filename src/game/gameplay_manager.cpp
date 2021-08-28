/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Andreea Scrob #989372
  08/13/2021

  gameplay_manager.cpp: implementation of Game::GameplayManager.
*/

#include "gameplay_manager.hpp"

#include "../world/chunk_assembler.hpp"


using Game::GameplayManager;

GameplayManager::GameplayManager(Data::Database &datab, Engine::Screen &scr)
    : screen(scr), menu_manager(datab, scr) {}

Game::MenuManager &GameplayManager::get_menu_manager() { return menu_manager; }

bool GameplayManager::can_stand(Data::MapUnit u) {
  return u == Data::MapUnit::nothing || u == Data::MapUnit::item ||
         u == Data::MapUnit::enemy;
}

bool GameplayManager::can_dig(Data::MapUnit u) {
  return can_stand(u) || u == Data::MapUnit::platform;
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
  if (player.second.move_left()) {
    auto &chunk = player.second.get_fragment()->map_chunk;
    auto unit =
        chunk->at(player.second.get_y()).at(player.second.get_x()).value();
    if (!can_stand(unit))
      player.second.move_right();
  }
}

void GameplayManager::move_right() {
  auto &player = menu_manager.get_world().player;
  if (player.second.move_right()) {
    auto &chunk = player.second.get_fragment()->map_chunk;
    auto unit =
        chunk->at(player.second.get_y()).at(player.second.get_x()).value();
    if (!can_stand(unit))
      player.second.move_left();
    else if (std::next(player.second.get_fragment()) ==
             menu_manager.get_world().environment.end()) {
      menu_manager.get_world().add_chunk(1);
      const size_t world_length = menu_manager.get_world().environment.size(),
                   music_duration =
                       2 * World::ChunkAssembler::sceneries_duration;
      if (world_length % music_duration == 0)
        switch ((world_length / music_duration) % 3) {
        case 0:
          menu_manager.get_settings_manager().play_soundtrack("theme1");
          break;
        case 1:
          menu_manager.get_settings_manager().play_soundtrack("theme2");
          break;
        case 2:
          menu_manager.get_settings_manager().play_soundtrack("theme3");
        }
    }
  }
}

void GameplayManager::move_up() {
  auto &player = menu_manager.get_world().player;
  auto &chunk = player.second.get_fragment()->map_chunk;
  if (player.second.get_y() + 1 < chunk->height) {
    auto unit_below =
        chunk->at(player.second.get_y() + 1).at(player.second.get_x()).value();
    if (player.second.get_y() != 0 && !can_stand(unit_below)) {
      auto unit_above = chunk->at(player.second.get_y() - 1)
                            .at(player.second.get_x())
                            .value();
      if (unit_above == Data::MapUnit::platform) { // dig platform
        menu_manager.get_world().player.second.move_up();
        menu_manager.get_world().player.second.move_up();
      } else { // attempt traditional jump
        int i = 2;
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
  }
}

void GameplayManager::move_down() {
  auto &player = menu_manager.get_world().player;
  auto &chunk = player.second.get_fragment()->map_chunk;
  if (player.second.get_y() + 1 ==
      player.second.get_fragment()->map_chunk->height)
    die();
  else {
    auto unit_below =
        chunk->at(player.second.get_y() + 1).at(player.second.get_x()).value();
    if (can_stand(unit_below))
      menu_manager.get_world().player.second.move_down();
  }
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

void GameplayManager::die() {
  menu_manager.set_message(Nostd::String());
  menu_manager.get_settings_manager().play_soundtrack("main_menu");
  screen.send_event(Engine::Drawable::Event::interact);
}