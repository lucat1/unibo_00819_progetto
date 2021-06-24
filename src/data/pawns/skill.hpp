/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Stefano Volpe #969766
  06/14/2021

  skill.hpp: user interface of Data::Pawns::Skill.
*/

#ifndef DATA_PAWNS_SKILL_HPP
#define DATA_PAWNS_SKILL_HPP

#include <istream>

namespace Data {

namespace Pawns {

class Skill {};

std::basic_istream<wchar_t> &operator>>(std::basic_istream<wchar_t> &, Skill &);

} // namespace Pawns

} // namespace Data

#endif
