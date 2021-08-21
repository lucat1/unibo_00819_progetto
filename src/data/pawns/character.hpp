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
  A Character is a Pawn able to move and fight. A generic Character only has one
  skill though.
*/
class Character : public virtual Pawn {
public:
  Character() = default;
  Character(const Nostd::String &, char = u' ',
            Engine::Color = Engine::Color::transparent, Skill = {},
            bool player = false);
  Character(Character &&) = default;
  Character &operator=(Character &&);
  Character(const Character &) = default;
  Character &operator=(const Character &) = default;

  virtual ~Character() = default;

  Skill skill() const noexcept;

private:
  Skill sk{};
};

} // namespace Pawns

} // namespace Data

#endif
