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
#include <memory>

#include "../engine/tile.hpp"
#include "../nostd/matrix.hpp"

namespace Data {

/*
  A Mugshot works as a detailed sprite to be shown during the game. It is
  represented as a Matrix of BlockTiles.
*/
class Mugshot : public Nostd::Matrix<const Engine::Tile *> {
public:
  Mugshot();
  Mugshot(Mugshot &&) = default;
  Mugshot &operator=(Mugshot &&) = default;
  Mugshot(const Mugshot &);
  Mugshot &operator=(const Mugshot &);

  ~Mugshot();

  constexpr static size_t side{12};
};

std::basic_istream<wchar_t> &operator>>(std::basic_istream<wchar_t> &,
                                        Mugshot &);

} // namespace Data

#include "../nostd/matrix.cpp"

#endif
