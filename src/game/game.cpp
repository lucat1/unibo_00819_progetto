/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Andreea Scrob #989372
  08/07/2021

  game.cpp: implementation of the main game logic.
*/

#include "game.hpp"
#include "../engine/audio.hpp"
#include "../engine/menu/main.hpp"
#include "../engine/menu/select.hpp"
#include "../engine/menu/settings.hpp"
#include "../engine/scene/scene.hpp"
#include <iostream>
#include <signal.h>
#include <unistd.h>
using Engine::Audio;
using Engine::Drawable;
using Engine::Menu::Main;
using Engine::Menu::Select;
using Engine::Menu::Settings;
using Engine::Scene::Scene;
using std::cout;

Game::Game::Game()
    : db("overengineered.conf.csv", "assets", "scoreboard.csv"), world(db) {
  apply_settings();
  signal(SIGTERM, before_close);
}

void Game::Game::before_close(int) { Audio::stop(); }

int Game::Game::run() {
  int e = play_soundtrack("main_menu");
  if (e != 0)
    return e + 1;

  if (!screen.open()) {
    cout << "Could not open screen. Perhaps your terminal is too small?\n";
    return 1;
  }

  screen.set_content<Main>();
  while (running) {
    running = loop();
  }
  screen.close();
  before_close(0); // useless parameter
  return 0;
}

bool Game::Game::loop() {
  // quit if usleep is blocked by an interrupt and the key is an ERR
  if (usleep(1000000 / fps) == EINTR)
    return false;

  bool b;
  if (screen.get_content()->is_over()) {
    if ((b = change_content()) != running)
      return b;
  } else if (in_game)
    screen.send_event(Engine::Drawable::Event::redraw);

  handle_keypress();
  return true;
}

bool Game::Game::change_content() {
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
      // TODO: change me
      /*screen.set_content<Menu::Results,
                         const Nostd::List<Data::Pawns::Result>
         &>(d.results());
                         */
      screen.set_content<Select, const Nostd::Vector<Data::Pawns::Hero> &>(
          db.heroes());
      break;
    default:
      break;
    }
  } else {
    // save settings if that was the previous menu
    if (screen.is_content<Settings>()) {
      db.settings() = screen.get_content<Settings>()->get_result();
      db.save_settings();
      apply_settings();
    }
    // TODO: write settings
    if (!screen.is_content<Select>()) {
      // go back to the main menu
      in_game = false;
      screen.set_content<Main>();
    } else {
      // otherwhise start a game
      // TODO: use this to provide the world a context of the current hero
      world.player.first = screen.get_content<Select>()->get_result();
      in_game = true;
      screen.set_content<Scene, const World::World &>(world);
    }
  }
  return true;
}

void Game::Game::handle_keypress() {
  int key = getch();
  switch (key) {
  case KEY_RESIZE:
    if (!screen.reposition())
      running = false;
    break;

  case '\n':
  case KEY_ENTER: // enter key for the numpad
    screen.send_event(Drawable::Event::interact);
    break;

  case 'k':
  case KEY_UP:
    if (!in_game)
      screen.send_event(Drawable::Event::move_up);
    else
      world.player.second->move_up();
    break;

  case 'j':
  case KEY_DOWN:
    if (!in_game)
      screen.send_event(Drawable::Event::move_down);
    else
      world.player.second->move_down();
    break;

  case 'h':
  case KEY_LEFT:
    if (!in_game)
      screen.send_event(Drawable::Event::move_left);
    else
      world.player.second->move_left();
    break;

  case 'l':
  case KEY_RIGHT:
    if (!in_game)
      screen.send_event(Drawable::Event::move_right);
    else
      world.player.second->move_right();
    break;
  case ERR:
    // ignore ncurses's getch errors
    break;
  };
}

int Game::Game::play_soundtrack(const char fn[]) {
  if (sound) {
    auto fp = db.to_audio_filepath(fn);
    switch (Audio::play(fp.c_str())) {
    case Audio::Error::none:
      return 0;
    case Audio::Error::no_tool:
      cout << "Could not play the soundtrack. Do you have aplay or afplay?\n";
      return 1;
    case Audio::Error::invalid_file:
      cout << "Could not play the soundtrack: invalid file (" << fp << ").\n";
      return 2;
    default:
      cout << "Could not play the soundtrack: unknown error.\n";
      return 3;
    }
  }
  return 0;
}

void Game::Game::apply_settings() {
  for (auto x : db.settings()) {
    if (x.label() == "Sounds") {
      sound = *x.current_value();
      if (!sound)
        Audio::stop();
      else if (Audio::status() == Audio::State::stopped)
        play_soundtrack("main_menu");
    } else if (x.label() == "Frames per second")
      fps = *x.current_value();
  }
}

void Game::Game::update_scoreboard() {
  auto &scoreboard = db.results();
  if (scoreboard.size() == 0)
    scoreboard.push_front(world.player.first);
  else {
    Nostd::List<Data::Pawns::Result>::iterator p;
    for (p = scoreboard.begin();
         p != scoreboard.end() && *p >= world.player.first.score(); p++)
      ;
    scoreboard.insert(p, world.player.first);
  }
}
