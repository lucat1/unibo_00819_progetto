#ifndef WORLD_POSITION_HPP
#define WORLD_POSITION_HPP

#include "../nostd/list.hpp"
#include "../nostd/matrix.hpp"
#include "../engine/screen.hpp"
#include "../engine/block_tile.hpp"
#include <iterator>

namespace World {
class Position {
  private :Nostd::List<Nostd::Matrix<Engine::BlockTile *>> environment;

public:
  Nostd::List<Nostd::Matrix<Engine::BlockTile *>>::iterator fragment;
  int x, y;

  Position(
  Nostd::List<Nostd::Matrix<Engine::BlockTile *>> environment) {
    this->environment = environment;
    this->x = 0;
    this->y = 5;
    this->fragment = environment.begin();
  }

  void dec_x() {
    if(x != 0)
      x--;
    else if(*fragment != *environment.begin()) {
      fragment = std::prev(fragment);
      x = (*fragment).extent(1)-1;
    }
  }

  void inc_x() {
    if((size_t)x != (*fragment).extent(1)-1)
      x++;
    else {
      fragment = std::next(fragment);
      x = 0;
    }
  }
};
}

#endif // WORLD_POSITION_HPP
