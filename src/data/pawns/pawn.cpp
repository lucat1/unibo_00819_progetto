/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Stefano Volpe #969766
  06/26/2021

  pawn.cpp: implementation of Data::Pawns::Pawn.
*/

#include "pawn.hpp"

#include <algorithm>

using Data::Pawns::Pawn;

Pawn::Pawn(Nostd::String name, char character, Engine::Color foreground)
    : Engine::EntityTile{character, foreground}, nm{name} {}

Pawn &Pawn::operator=(Pawn &&p) {
  if (!p.movedFrom) {
    std::swap(nm, p.nm);
    p.movedFrom = true;
  }
  return *this;
}

const Nostd::String &Pawn::name() const noexcept { return nm; }
