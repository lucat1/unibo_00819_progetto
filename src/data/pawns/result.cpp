/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Stefano Volpe #969766
  04/03/2021

  result.cpp: implementation of Data::Pawns::Result.
*/

#include "result.hpp"

#include <iostream>
#include <stdexcept>

using Data::Pawns::Result;
using Nostd::WString;

Result::Result(const WString &name, wchar_t character, Engine::Color foreground,
               int score)
    : Engine::EntityTile{character, foreground},
      Pawn{name, character, foreground}, scr{score} {
  if (score < 0)
    throw std::invalid_argument("score < 0");
}

Result::Result(Data::Pawns::Hero h)
    : Result(h.name(), h.character(), h.foreground(), h.score()) {}

int Result::score() const noexcept { return scr; }

Result::operator int() const { return scr; }
