/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Stefano Volpe #969766
  06/14/2021

  pawn.cpp: implementation of Data::Pawns::Pawn.
*/

#include "pawn.hpp"

Data::Pawns::Pawn::Pawn(const Nostd::WString &s) : n{s} {}

const Nostd::WString &Data::Pawns::Pawn::name() const { return n; }
