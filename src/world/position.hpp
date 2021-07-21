#ifndef WORLD_POSITION_HPP
#define WORLD_POSITION_HPP

#include "../nostd/list.hpp"
#include "../nostd/matrix.hpp"
#include "../engine/screen.hpp"
#include "../engine/block_tile.hpp"
#include <iterator>

namespace World {
class Position {
public:
  Nostd::List<Nostd::Matrix<Engine::BlockTile *>>::iterator fragment;
  int x, y;

  Position(
  Nostd::List<Nostd::Matrix<Engine::BlockTile *>> environment) {
    x = Engine::Screen::columns / 2;
    y = Engine::Screen::lines / 2;
    auto it = environment.begin();
    int xx = 0;
    while(xx + (int)(*it).extent(1) < x) {
      xx += (*it).extent(1);
      it = std::next(it);
    }
    fragment = it;
  }
};
}

#endif // WORLD_POSITION_HPP
