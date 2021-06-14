/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Stefano Volpe #969766
  04/03/2021

  result.cpp: implementation of Data::Result.
*/

#include "result.hpp"

#include <stdexcept>

using Data::Result;
using Data::Pawns::Hero;
using Nostd::WString;

Result::Result(const WString &nickname, const Hero *hero, int score)
    : nick{nickname}, hr{hero}, scr{score} {
  if (score < 0)
    throw std::invalid_argument("score < 0");
}

const WString &Result::nickname() const noexcept { return nick; }

const Hero *Result::hero() const noexcept { return hr; }

int Result::score() const noexcept { return scr; }

Result::operator int() const { return scr; }
