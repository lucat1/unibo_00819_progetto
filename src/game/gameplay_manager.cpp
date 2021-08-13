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
