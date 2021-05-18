/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Stefano Volpe #969766
  04/06/2021

  Luca Tagliavini #971133
  04/26/2021

  palette.hpp: constants defined in Data::Palette.
*/

#ifndef DATA_PALETTE_HPP
#define DATA_PALETTE_HPP

#include "../engine/colorable.hpp"
#include "../nostd/pair.hpp"

using Engine::Color;

namespace Data {
namespace Palette {

using Subpalette = Nostd::Pair<Color, Color>;

constexpr Color primary = Color::red, secondary = Color::aqua,
                unfocused = Color::grey23;
constexpr Subpalette logo(primary, Color::transparent),
    button(secondary, unfocused), slider(secondary, Color::transparent);

} // namespace Palette
} // namespace Data

#endif
