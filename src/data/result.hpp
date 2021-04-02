/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Stefano Volpe #969766
  04/02/2021

  result.hpp: user interface of Data::Result and its helper entities.
*/

#ifndef DATA_RESULT_HPP
#define DATA_RESULT_HPP

#include "../nostd/wstring.hpp"
#include "interactables/hero.hpp"

namespace Data {

/*
  A Result describes the aftermath of a single game. It stores the
  player's nickname, a reference to the Hero they used and their score.
*/
class Result {
public:
private:
  Nostd::WString nick;
  const Interactables::Hero *chr;
  int pts;
};

} // namespace Data

#endif
