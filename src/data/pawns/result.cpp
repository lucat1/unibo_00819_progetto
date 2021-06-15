/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Stefano Volpe #969766
  04/03/2021

  result.cpp: implementation of Data::Pawns::Result.
*/

#include "result.hpp"

#include <stdexcept>

using Data::Pawns::Result;
using Nostd::WString;

Result::Result(const WString &name, int score, Engine::Color foreground,
               wchar_t character)
    : nm{name}, scr{score}, fg{foreground}, chr{character} {
  if (score < 0)
    throw std::invalid_argument("score < 0");
}

Result::Result(Data::Pawns::Hero h)
    : Result(h.name(), h.score(), h.foreground(), h.character()) {}

const WString &Result::name() const noexcept { return nm; }

int Result::score() const noexcept { return scr; }

Engine::Color Result::foreground() const noexcept { return fg; }

wchar_t Result::character() const noexcept { return chr; }

Result::operator int() const { return scr; }
