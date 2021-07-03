/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Stefano Volpe #969766
  04/02/2021

  result.hpp: user interface of Data::Pawns::Result.
*/

#ifndef DATA_PAWNS_RESULT_HPP
#define DATA_PAWNS_RESULT_HPP

#include "../../engine/colorable.hpp"
#include "../../nostd/wstring.hpp"
#include "hero.hpp"
#include "pawn.hpp"

namespace Data {

namespace Pawns {

/*
  A Result describes the aftermath of a single game. It stores the
  player's name, a reference to the Hero they used and their score (which
  must not be negative).
*/
class Result : public Pawn {
public:
  Result() = default;
  Result(const Nostd::WString &, char = u' ',
         Engine::Color = Engine::Color::transparent, int = 0);
  Result(Hero);
  Result(Result &&) = default;
  Result &operator=(Result &&) = default;
  Result(const Result &) = default;
  Result &operator=(const Result &) = default;

  virtual ~Result() = default;

  int score() const noexcept;
  operator int() const; // converts results to scores (so they can be compared)

private:
  int scr{0};
};

} // namespace Pawns

} // namespace Data

#endif
