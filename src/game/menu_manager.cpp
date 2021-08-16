/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Andreea Scrob #989372
  08/13/2021

  menu_manager.cpp: implementation of Game::MenuManager.
*/
#include "menu_manager.hpp"
#include "../data/database.hpp"
#include "../engine/menu/main.hpp"
#include "../engine/menu/results.hpp"
#include "../engine/menu/select.hpp"
#include "../engine/menu/settings.hpp"
#include "../engine/scene/scene.hpp"

using Engine::Menu::Main;
using Engine::Menu::Results;
using Engine::Menu::Select;
using Engine::Menu::Settings;
using Engine::Scene::Scene;
using Game::MenuManager;

MenuManager::MenuManager(Data::Database &datab, Engine::Screen &scr)
    : db(datab), screen(scr), settings_manager(datab) {}

bool MenuManager::change_content() {
  if (screen.is_content<Main>()) {
    // do something when the main menu is exited
    auto res = screen.get_content<Main>()->get_result();
    switch (res) {
    case Main::Result::quit:
      return false;
      break;
    case Main::Result::settings:
      screen.set_content<Settings, const Nostd::Vector<Data::Setting> &>(
          db.settings());
      break;
    case Main::Result::play:
      screen.set_content<Select, const Nostd::Vector<Data::Pawns::Hero> &>(
          db.heroes());
      break;
    default:
      break;
    }
  } else if (screen.is_content<Scene>()) {
    update_scoreboard();
    delete world;
    world = nullptr;
    db.save_results();
    screen.set_content<Results, const Nostd::List<Data::Pawns::Result> &>(
        db.results());
  } else {
    // save settings if that was the previous menu
    if (screen.is_content<Settings>()) {
      db.settings() = screen.get_content<Settings>()->get_result();
      db.save_settings();
      settings_manager.apply_settings();
    }
    if (!screen.is_content<Select>()) {
      // go back to the main menu
      in_game = false;
      screen.set_content<Main>();
    } else {
      // otherwhise start a game
      world = new World::World(db, screen.get_content<Select>()->get_result());
      in_game = true;
      screen.set_content<Scene, const World::World &>(*world);
    }
  }
  return true;
}
void MenuManager::update_scoreboard() {
  auto &scoreboard = db.results();
  if (scoreboard.size() == 0)
    scoreboard.push_front(world->player.first);
  else {
    Nostd::List<Data::Pawns::Result>::iterator p;
    for (p = scoreboard.begin();
         p != scoreboard.end() && *p >= world->player.first.score(); p++)
      ;
    scoreboard.insert(p, world->player.first);
  }
}
Game::SettingsManager &MenuManager::get_settings_manager() {
  return settings_manager;
}
bool MenuManager::is_in_game() { return in_game; }
World::World &MenuManager::get_world() { return *world; }