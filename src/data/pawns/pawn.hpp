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

#include "../../engine/tile.hpp"
#include "../../nostd/wstring.hpp"

namespace Data {
namespace Pawns {

/*
  A Pawn is simply a named Tile. In other words, every single-cell entity on the
  map which deserves a name of their own is a Pawn.
*/
class Pawn : public Engine::Tile {
protected:
  Pawn(const Nostd::WString &);

public:
  const Nostd::WString &name() const;

private:
  Nostd::WString n;
};

} // namespace Pawns
} // namespace Data

#endif
