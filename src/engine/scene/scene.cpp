/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Luca Tagliavini #971133
  07/02/2021

  scene.cpp: TODO as we properly render stuff here
*/

#include "scene.hpp"
#include "../../world/world.hpp"
#include "../screen.hpp"
#include "hud.hpp"
#include <exception>

Engine::Scene::Scene::Scene(WINDOW *window, const World::World &world)
    : Drawable(window, Screen::columns, Screen::lines), world{world} {}

Engine::Drawable::Kind Engine::Scene::Scene::kind() const { return Kind::game; }

void Engine::Scene::Scene::handle_event(Event e) {
  if (e != Event::redraw)
    over = true;
  // TODO: restore, this is the proper mechanic
  /* throw std::invalid_argument("Engine::Scene::Scene only handles " */
  /*                             "Engine::Drawable::Event::redraw events"); */
  draw();
}

bool Engine::Scene::Scene::is_over() { return over; }

void Engine::Scene::Scene::draw() {
  // do all serious rendering first, lastly render the HUD
  Data::Pawns::Hero p = world.player;

  // draw HUD
  HUD hud(p.currentHealth(), p.maxHealth(), p.currentMana(), p.maxMana(),
          p.score());
  hud.show(window, 0, Screen::lines - 1, Screen::columns, 1);

  // draw the world around the player
  // TODO: await proper implementation
  auto pos = world.position;
  int left = 0, right = 0;
  pos->fragment

  // ncurses redraw
  doupdate();
}
