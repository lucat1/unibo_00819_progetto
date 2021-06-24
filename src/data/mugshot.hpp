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
class MugshotTile : public Engine::Tile {
public:
  MugshotTile(Engine::Color foreground, Engine::Color background,
              wchar_t character);
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

std::basic_istream<wchar_t> &operator>>(std::basic_istream<wchar_t> &,
                                        MugshotTile &);
std::basic_ostream<wchar_t> &operator<<(std::basic_ostream<wchar_t> &,
                                        MugshotTile);

/*
  A Mugshot works as a detailed sprite to be shown during the game. It is
  represented as a Matrix of MugshotTiles.
*/
class Mugshot : public Nostd::Matrix<MugshotTile> {
public:
  Mugshot();
  Mugshot(Mugshot &&) = default;
  Mugshot &operator=(Mugshot &&) = default;
  Mugshot(const Mugshot &) = default;
  Mugshot &operator=(const Mugshot &) = default;

  constexpr static size_t side{12};
};

std::basic_istream<wchar_t> &operator>>(std::basic_istream<wchar_t> &,
                                        Mugshot &);

} // namespace Data

#include "../nostd/matrix.cpp"

#endif
