/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Stefano Volpe #969766
  06/14/2021

  character.hpp: user interface of Data::Pawns::Character.
*/

#ifndef DATA_PAWNS_CHARACTER_HPP
#define DATA_PAWNS_CHARACTER_HPP

#include "pawn.hpp"
#include "skill.hpp"

namespace Data {

namespace Pawns {

/*
  A Character is a Pawn able to move and fight. It may be able to fly and can
  count on a basic skill to use.
*/
class Character : public Pawn {
public:
  virtual bool canFly() const;
  virtual Skill skill() const = 0;
};

} // namespace Pawns

} // namespace Data

#endif
