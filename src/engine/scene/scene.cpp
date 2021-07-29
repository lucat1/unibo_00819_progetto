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
  // start with a blank slate
  werase(window);

  // draw the world around the player
  // TODO: await proper implementation
  auto pos = world.position;
  // the drawing of the map is handled in this way:
  // 1. compute the *first* chunk to be drawn
  // 2. adress the initial position of the player when there is no world to the
  // left
  // 3. draw from there on until we exceed the screen width
  auto start = pos->fragment; // assume the player is in the first chunk
  size_t first_offset = 0,
         player_x = pos->get_x(); // assuming the player is behind the threshold
  if (pos->get_x() > width / 2) {
    // the chunk is wide enough to center the player
    first_offset = pos->get_x() - width / 2;
    player_x = width / 2;
  } else if (*start != *world.environment.begin()) {
    // traverse backwards $n$ chunks until we have no more screen space left to
    // fill. then the value of space_left will be the offset of the first chunk
    auto space_left = (width / 2) - pos->get_x();
    start = std::prev(start);
    while ((space_left -= (*start).extent(1)) > 0)
      start = std::prev(start);

    first_offset = std::abs(space_left);
    player_x = width / 2;
  }
  // phase 3: draw the chunks from the left-most until we have screen space
  size_t filled = 0;
  while (filled < width) {
    draw_chunk(*start, filled, 0, first_offset);
    filled += (*start).extent(1) - first_offset;
    start = std::next(start);
    if (first_offset != 0)
      first_offset = 0;
  }

  // draw the player charter
  // gather the background from the player's current fragment and the foreground
  // from the Hero class
  int pair = Engine::UI::color_pair(
      color_to_short(world.player.foreground()),
      color_to_short(
          (*pos->fragment)[pos->get_y()][pos->get_x()].value()->background()));
  Engine::UI::start_color(window, pair);
  mvwaddch(window, pos->get_y(), player_x, world.player.character());
  Engine::UI::end_color(window, pair);

  // lastly render the HUD
  Data::Pawns::Hero p = world.player;
  HUD hud(p.currentHealth(), p.maxHealth(), p.currentMana(), p.maxMana(),
          p.score());
  hud.show(window, 0, Screen::lines - 1, Screen::columns, 1);
  wnoutrefresh(window);
  doupdate();
}

// TODO: y offsetting, when needed
void Engine::Scene::Scene::draw_chunk(Nostd::Matrix<BlockTile *> chunk, int x,
                                      int y, int offset_x, int offset_y) {
  // draw until we're out of the screen
  size_t mx = offset_x, my = offset_y;
  int x_cpy = x;
  while (y < height && my < chunk.extent(0)) {
    while (x < width && mx < chunk.extent(1)) {
      auto tile = chunk[my][mx].value();
      int pair = Engine::UI::color_pair(color_to_short(tile->foreground()),
                                        color_to_short(tile->background()));
      Engine::UI::start_color(window, pair);
      mvwaddch(window, y, x, tile->character());
      Engine::UI::end_color(window, pair);
      x++;
      mx++;
    }
    y++;
    my++;
    x = x_cpy;
    mx = offset_x;
  }
}
