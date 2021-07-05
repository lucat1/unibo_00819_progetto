/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Luca Tagliavini #971133
  07/02/2021

  scene.cpp: TODO as we properly render stuff here
*/

#include "scene.hpp"
#include "../screen.hpp"
#include "hud.hpp"
#include <exception>

Engine::Scene::Scene::Scene(WINDOW *window, const Data::Pawns::Hero &hero)
    : Drawable(window, Screen::columns, Screen::lines), player{hero} {
  // TODO: remove when we recieve a proper world object with the map and
  // entities data
}

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

  // draw HUD
  HUD hud(player.currentHealth(), player.maxHealth(), player.currentMana(),
          player.maxMana());
  hud.show(window, 0, Screen::lines - 1, Screen::columns, 1);

  doupdate();
}
