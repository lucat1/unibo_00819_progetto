/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Stefano Volpe #969766
  04/02/2021

  hero.hpp: user interface of Data::Interactables::Hero and its helper entities.
*/

#ifndef DATA_INTERACTABLES_HERO_HPP
#define DATA_INTERACTABLES_HERO_HPP

#include "../../nostd/wstring.hpp"

namespace Data {

namespace Interactables {

/*
  A Hero is a playable character: as such, it provides a health and a mana
  gauge, as well as a description.
*/
class Hero {
public:
  const Nostd::WString &name() const noexcept;
  wchar_t sprite() const noexcept;

private:
  Nostd::WString nm{L""};
  wchar_t sprt{'\0'};
};

} // namespace Interactables

} // namespace Data

#endif
