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
    : db(datab), menu_manager(datab, scr) {}

Game::MenuManager &GameplayManager::get_menu_manager() { return menu_manager; }

void Game::GameplayManager::move_left() {
  menu_manager.get_world().player.second.move_left();
}
void Game::GameplayManager::move_right() {
  menu_manager.get_world().player.second.move_right();
}
void Game::GameplayManager::move_up() {
  menu_manager.get_world().player.second.move_up();
}
void Game::GameplayManager::move_down() {
  menu_manager.get_world().player.second.move_down();
}
