/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Stefano Volpe #969766
  04/06/2021

  scenery.hpp: user interface of Data::Scenery and its helper entities.
*/

#ifndef DATA_SCENERY_HPP
#define DATA_SCENERY_HPP

#include <istream>

#include "../engine/colorable.hpp"
#include "../nostd/vector.hpp"

namespace Data {

/*
  A Scenery expresses an aesthetic which can be applied to any portion of the
  game world. It specifies characters and colors.
*/
struct Scenery {

  /*
    An Autotile provides a set of tiles picked to be automatically arranged to
    form any kind of shape.
  */
  struct Autotile {
    char singlet,                                  // ▢
        concave_top_left, concave_top_right,       // ⌟⌞
        concave_bottom_left, concave_bottom_right, // ⌝⌜
        top_left, top, top_right,                  // ⎡⎺⎤
        left, center, right,                       // ⎢⩩⎥
        bottom_left, bottom, bottom_right;         // ⎣⎯⎦
    Engine::Color foreground, background;          // 9 0
  } ground, platform;
  Nostd::Vector<Engine::Color> sky; // the sky may have multiple shades
};

// A stream can represent a Scenery using:
// - seven lines for the ground Autotile (as shown above)
// - seven lines for the foreground Autotile (as shown above)
// - a single line with the number of the color in the sky followed by a single
//   code for each of them
std::basic_istream<char> &operator>>(std::basic_istream<char> &,
                                     Scenery::Autotile &);

std::basic_istream<char> &operator>>(std::basic_istream<char> &, Scenery &);

} // namespace Data

#endif
