/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Stefano Volpe #969766
  06/15/2021

  skill.cpp: implementation of Data::Pawns::Skill.
*/

#include "skill.hpp"

#include <istream>

using Data::Pawns::Skill;

std::basic_istream<wchar_t> &
Data::Pawns::operator>>(std::basic_istream<wchar_t> &is, Skill &s) {
  return is; // TODO mockup implementation
}
