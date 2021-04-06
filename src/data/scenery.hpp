/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Stefano Volpe #969766
  04/06/2021

  scenery.hpp: user interface of Data::Scenery.
*/

#ifndef DATA_SCENERY_HPP
#define DATA_SCENERY_HPP

#include "../engine/colorable.hpp"

namespace Data {

struct Scenery {
  struct Autotile {
    struct Tile : public Engine::Colorable {};
  };
};

} // namespace Data

#endif
