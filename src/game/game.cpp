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
#include "../engine/menu/results.hpp"
#include "../engine/menu/select.hpp"
#include "../engine/menu/settings.hpp"
#include "../engine/scene/scene.hpp"
#include <iostream>
#include <signal.h>
#include <unistd.h>
using Engine::Audio;
using Engine::Drawable;
using Engine::Menu::Main;
using std::cout;

Game::Game::Game()
    : db("overengineered.conf.csv", "assets", "scoreboard.csv"),
      gameplay_manager(db, screen) {
  gameplay_manager.get_menu_manager().get_settings_manager().apply_settings();
  signal(SIGTERM, before_close);
}

void Game::Game::before_close(int) { Audio::stop(); }

int Game::Game::run() {
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
  int fps =
      gameplay_manager.get_menu_manager().get_settings_manager().get_fps();
  // quit if usleep is blocked by an interrupt and the key is an ERR
  if (usleep(1000000 / fps) == EINTR)
    return false;

  bool b;
  if (screen.get_content()->is_over()) {
    if ((b = gameplay_manager.get_menu_manager().change_content()) != running)
      return b;
  } else if (gameplay_manager.get_menu_manager().is_in_game()) {
    if ((frame / (fps / 10)) % 3 == 0)
      gameplay_manager.gravity();
    screen.send_event(Engine::Drawable::Event::redraw);
  }

  handle_keypress();
  if (gameplay_manager.get_menu_manager().is_in_game())
    gameplay_manager.manage_items();

  frame += 2;
  if (frame > fps * 20)
    frame = 1;
  return true;
}

void Game::Game::handle_keypress() {
  int key = getch();
  if (gameplay_manager.get_menu_manager().is_in_game()) {
    if (last_key == 'e')
      gameplay_manager.move_right();
    else if (last_key == 'q')
      gameplay_manager.move_left();
  }
  switch (key) {
  case KEY_RESIZE:
    if (!screen.reposition())
      running = false;
    break;
  case '\n':
  case KEY_ENTER: // enter key for the numpad
    if (!gameplay_manager.get_menu_manager().is_in_game())
      screen.send_event(Drawable::Event::interact);
    break;

  case 'k':
  case 'w':
  case KEY_UP:
    if (!gameplay_manager.get_menu_manager().is_in_game())
      screen.send_event(Drawable::Event::move_up);
    else
      gameplay_manager.move_up();
    break;
  case 'q':
    if (gameplay_manager.get_menu_manager().is_in_game()) {
      gameplay_manager.move_up();
      gameplay_manager.move_left();
    }
    break;
  case 'e':
    if (gameplay_manager.get_menu_manager().is_in_game()) {
      gameplay_manager.move_up();
      gameplay_manager.move_right();
    }
    break;
  case 'j':
  case 's':
  case KEY_DOWN:
    if (!gameplay_manager.get_menu_manager().is_in_game())
      screen.send_event(Drawable::Event::move_down);
    else {
      gameplay_manager.move_dig();
      gameplay_manager.move_dig();
    }
    break;

  case 'h':
  case 'a':
  case KEY_LEFT:
    if (!gameplay_manager.get_menu_manager().is_in_game())
      screen.send_event(Drawable::Event::move_left);
    else
      gameplay_manager.move_left();
    break;

  case 'l':
  case 'd':
  case KEY_RIGHT:
    if (!gameplay_manager.get_menu_manager().is_in_game())
      screen.send_event(Drawable::Event::move_right);
    else
      gameplay_manager.move_right();
    break;
  case '\33': // ESC key = suicide
    gameplay_manager.die();
    break;
  case ERR:
    // ignore ncurses's getch errors
    break;
  };
  last_key = key;
}
