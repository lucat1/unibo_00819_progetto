/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Stefano Volpe #969766
  04/06/2021

  palette.hpp: constants defined in Data::Palette.
*/

#ifndef DATA_PALETTE_HPP
#define DATA_PALETTE_HPP

#include "../engine/colorable.hpp"
#include "../nostd/pair.hpp"

namespace Data {
namespace Palette {

using Color = Engine::Color;
using Subpalette = Nostd::Pair<Color, Color>;

constexpr Subpalette logo(Color::red, Color::black),
    frame(Color::grey23, Color::black), button(Color::red, Color::grey23),
    slider(Color::grey50, Color::white),
    message(Color::navajo_white1, Color::grey23),
    gauge(Color::red, Color::grey50);

} // namespace Palette
} // namespace Data

#endif
