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
  // compute the amout of drawing needed on the sides of the player (taking into
  // account the beginning of the map where we can't center the player)
  /* int left = std::min(pos.x, width / 2), */
  /*     right = std::max(width - pos.x, width / 2); */
  // draw the chunk the player is currently on
  draw_chunk(*(pos->fragment), 0, 0);
  /* while(left > 0) { */
  /* } */
  /* while(right > 0) { */
  /* } */

  mvwaddch(window, pos->y, pos->x, 'p');
  // ncurses redraw
  wnoutrefresh(window);
  doupdate();
}

void Engine::Scene::Scene::draw_chunk(Nostd::Matrix<BlockTile *> chunk, int x, int y) {
  // draw until we're out of the screen
  size_t mx = 0, my = 0;
  int x_cpy = x;
  while(y < height && my < chunk.extent(0)) {
    while(x < width && mx < chunk.extent(1)) {
      auto tile = chunk[my][mx].value();
      int pair = Engine::UI::color_pair(color_to_short(tile->foreground()), color_to_short(tile->background()));
      Engine::UI::start_color(window, pair);
      mvwaddch(window, y, x, tile->character());
      Engine::UI::end_color(window, pair);
      x++; mx++;
    }
    y++; my++;
    x =x_cpy; mx = 0;
  }
}
