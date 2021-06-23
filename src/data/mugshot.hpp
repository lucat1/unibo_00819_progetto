/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Stefano Volpe #969766
  06/23/2021

  mugshot.hpp: user interface of Data::Mugshot and its helper entities.
*/

#ifndef DATA_MUGSHOT_HPP
#define DATA_MUGSHOT_HPP

#include <istream>
#include <ostream>

#include "../engine/tile.hpp"
#include "../nostd/matrix.hpp"

namespace Data {

/*
  A MugshotTile, as its name suggests, is the basic unit of a Mugshot.
  MugshotTile is a simple implementation of Tile.
*/
class MugshotTile : Engine::Tile {
public:
  MugshotTile() = default;
  MugshotTile(MugshotTile &&) = default;
  MugshotTile &operator=(MugshotTile &&) = default;
  MugshotTile(const MugshotTile &) = default;
  MugshotTile &operator=(const MugshotTile &) = default;

  ~MugshotTile() = default;

  Engine::Color foreground() const noexcept override final;
  Engine::Color background() const noexcept override final;
  wchar_t character() const noexcept override final;

  bool operator==(MugshotTile) const noexcept;
  bool operator!=(MugshotTile) const noexcept;

private:
  Engine::Color fg{Engine::Color::transparent}, bg{Engine::Color::transparent};
  wchar_t chr{L' '};
};

std::istream &operator>>(std::istream &is, MugshotTile &);
std::ostream &operator<<(std::ostream &os, const MugshotTile &);

/*
  A Mugshot works as a detailed sprite to be shown during the game. It is
  represented as a Matrix of MugshotTiles.
*/
class Mugshot : Nostd::Matrix<MugshotTile> {};

} // namespace Data

#endif
