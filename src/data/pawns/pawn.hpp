/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Stefano Volpe #969766
  06/14/2021

  pawn.hpp: user interface of Data::Pawns::Pawn.
*/

#ifndef DATA_PAWNS_PAWN_HPP
#define DATA_PAWNS_PAWN_HPP

#include <istream>

#include "../../engine/entity_tile.hpp"
#include "../../nostd/string.hpp"

namespace Data {

namespace Pawns {

/*
  A Pawn is simply a named EntityTile. In other words, every single-cell entity
  on the map which deserves a name of their own is a Pawn.
*/
class Pawn : public virtual Engine::EntityTile {
public:
  Pawn() = default;
  Pawn(Nostd::String, char = u' ', Engine::Color = Engine::Color::transparent);
  Pawn(Pawn &&) = default;
  Pawn &operator=(Pawn &&);
  Pawn(const Pawn &) = default;
  Pawn &operator=(const Pawn &) = default;

  virtual ~Pawn() override = default;

  const Nostd::String &name() const noexcept;

protected:
  /*
    "Members declared protected are far more open to abuse than members declared
    private. In particular, declaring data members protected is usually a design
    error." B. Stroustrup, The C++ Programming Language, 4th ed., Pearson 2013,
    p. 604f.
    In this case, though, we want child classes to have unrestricted write
    privileges to a data member, and the general user to have none.
  */
  Nostd::String nm{"???"};
  bool movedFrom{false};
};

} // namespace Pawns

} // namespace Data

#endif
