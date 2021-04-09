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

#include <istream>

#include "../engine/colorable.hpp"
#include "../nostd/vector.hpp"

namespace Data {

struct Scenery {
  struct Autotile {
    wchar_t singlet,                               // ▢
        concave_top_left, concave_top_right,       // ⌟⌞
        concave_bottom_left, concave_bottom_right, // ⌝⌜
        top_left, top, top_right,                  // ⎡⎺⎤
        left, center, right,                       // ⎢⩩⎥
        bottom_left, bottom, bottom_right;         // ⎣⎯⎦
    Engine::Color foreground, background;
  } ground, platform;
  Nostd::Vector<Engine::Color> sky;
};

// A stream can represent a Scenery using:
// - six lines for the ground Autotile (as shown above)
// - six lines for the foreground Autotile (as shown above)
// - a single line with the number of the color in the sky followed by a single
//   code for each of them
std::basic_istream<wchar_t> &operator>>(std::basic_istream<wchar_t> &,
                                        Scenery::Autotile &);

std::basic_istream<wchar_t> &operator>>(std::basic_istream<wchar_t> &,
                                        Scenery &);

} // namespace Data

#endif
