/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Stefano Volpe #969766
  06/26/2021

  character.cpp: implementation of Data::Pawns::Character.
*/

#include "character.hpp"

#include <algorithm>

using Data::Pawns::Character;

Character::Character(const Nostd::String &name, char character,
                     Engine::Color foreground, Skill skill)
    : Pawn{name, character, foreground}, sk{skill} {}

Character &Character::operator=(Character &&c) {
  Pawn::operator=(c);
  std::swap(sk, c.sk);
  return *this;
}

auto Character::skill() const noexcept -> Skill { return sk; }
