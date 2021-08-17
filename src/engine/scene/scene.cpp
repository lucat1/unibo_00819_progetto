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
#include <exception>

Engine::Scene::Scene::Scene(WINDOW *window, const World::World &world,
                            const Nostd::String &message)
    : Drawable(window, Screen::columns, Screen::lines), world{world},
      message{message}, hud{world.player.first, message} {}

Engine::Drawable::Kind Engine::Scene::Scene::kind() const { return Kind::game; }

void Engine::Scene::Scene::handle_event(Event e) {
  // when we recieve an event different from the usual redraw message we know
  // the game has ended and we can close this drawable.
  if (e != Event::redraw)
    over = true;
  draw();
}

bool Engine::Scene::Scene::is_over() { return over; }

void Engine::Scene::Scene::draw() {
  // start with a blank slate
  werase(window);

  // draw the world around the player
  // TODO: await proper implementation
  auto pos = world.player.second;
  // the drawing of the map is handled in this way:
  // 1. compute the *first* chunk to be drawn
  // 2. adress the initial position of the player when there is no world to the
  // left
  // 3. draw from there on until we exceed the screen width
  auto start = pos.get_fragment(); // assume the player is in the first chunk
  size_t first_offset = 0,
         player_x = pos.get_x(); // assuming the player is behind the threshold
  if (pos.get_x() > width / 2) {
    // the chunk is wide enough to center the player
    first_offset = pos.get_x() - width / 2;
    player_x = width / 2;
  } else if (start != world.environment.begin()) {
    // traverse backwards $n$ chunks until we have no more screen space left to
    // fill. then the value of space_left will be the offset of the first chunk
    int space_left = (width / 2) - pos.get_x();
    start = std::prev(start);
    while ((space_left -= start->tiles.extent(1)) > 0)
      start = std::prev(start);

    first_offset = std::abs(space_left);
    player_x = width / 2;
  }
  // phase 3: draw the chunks from the left-most until we have screen space
  size_t filled = 0;
  while (filled < width) {
    draw_chunk(start->tiles, start->enemies, start->items, start->projectiles, filled, 0,
               first_offset);
    filled += start->tiles.extent(1) - first_offset;
    start = std::next(start);
    if (first_offset != 0)
      first_offset = 0;
  }

  // draw the player charter
  // gather the background from the player's current fragment and the foreground
  // from the Hero class
  int pair = Engine::UI::color_pair(
      color_to_short(world.player.first.foreground()),
      color_to_short(pos.get_fragment()
                         ->tiles[pos.get_y()][pos.get_x()]
                         .value()
                         ->background()));
  Engine::UI::start_color(window, pair);
  mvwaddch(window, pos.get_y(), player_x, world.player.first.character());
  Engine::UI::end_color(window, pair);

  // lastly render the HUD
  auto p = world.player.first;
  hud.show(window, 0, Screen::lines - 1, Screen::columns, 1);
  wnoutrefresh(window);
  doupdate();
}

// TODO: y offsetting, when needed
void Engine::Scene::Scene::draw_chunk(
    const Nostd::Matrix<Tile *> &tiles,
    const Nostd::Matrix<Data::Pawns::Enemy *> &enemies,
    const Nostd::Matrix<Data::Pawns::Item *> &items,
    const Nostd::Matrix<Data::Pawns::Projectile *> &projectiles, int x, int y,
    int offset_x, int offset_y) {
  // draw until we're out of the screen
  size_t mx = offset_x, my = offset_y;
  int x_cpy = x;
  while (y < height && my < tiles.extent(0)) {
    while (x < width && mx < tiles.extent(1)) {
      auto tile = tiles.at(my).at(mx).value();
      auto enemy = enemies.at(my).at(mx).value();
      auto item = items.at(my).at(mx).value();
      auto projectile = projectiles.at(my).at(mx).value();

      Engine::Tile *t;
      if (enemy != nullptr)
        t = enemy;
      else if (item != nullptr)
        t = item;
      else if (projectile != nullptr)
        t = projectile;
      else
        t = tile;

      Color bg = t->background();
      if(bg == Color::transparent)
        bg = tile->background();

      int pair = Engine::UI::color_pair(color_to_short(t->foreground()),
                                        color_to_short(bg));
      Engine::UI::start_color(window, pair);
      mvwaddch(window, y, x, t->character());
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
