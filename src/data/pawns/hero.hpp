/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Stefano Volpe #969766
  04/02/2021

  hero.hpp: user interface of Data::Pawns::Hero.
*/

#ifndef DATA_PAWNS_HERO_HPP
#define DATA_PAWNS_HERO_HPP

#include "../../nostd/wstring.hpp"
#include "character.hpp"

namespace Data {

namespace Pawns {

/*
  A Hero is a playable character: as such, it provides a health and a mana
  gauges, as well as a description and an additional skill.
*/
class Hero : Character {
public:
  const Nostd::WString &name() const noexcept;
  wchar_t sprite() const noexcept;

private:
  Nostd::WString nm{L""};
  wchar_t sprt{'\0'};
};

} // namespace Pawns

} // namespace Data

#endif
