#ifndef WORLD_POSITION_HPP
#define WORLD_POSITION_HPP

#include "../engine/block_tile.hpp"
#include "../engine/screen.hpp"
#include "../nostd/list.hpp"
#include "../nostd/matrix.hpp"
#include <iterator>

namespace World {
class Position {
private:
  Nostd::List<Nostd::Matrix<Engine::BlockTile *>> environment;
  int x;
  int y;

public:
  Nostd::List<Nostd::Matrix<Engine::BlockTile *>>::iterator fragment;

  Position(Nostd::List<Nostd::Matrix<Engine::BlockTile *>> environment) {
    this->environment = environment;
    this->x = 0;
    this->y = 19;
    this->fragment = environment.begin();
  }

  int get_x() const noexcept;
  int get_y() const noexcept;
  void set_x(const int &) noexcept;
  void set_y(const int &) noexcept;

  void move_left() noexcept;

  void move_right() noexcept;

  void move_down() noexcept;

  void move_up() noexcept;
};
} // namespace World

#endif // WORLD_POSITION_HPP
