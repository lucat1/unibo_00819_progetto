/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Stefano Volpe #969766
  04/02/2021

  result.hpp: user interface of Data::Result.
*/

#ifndef DATA_RESULT_HPP
#define DATA_RESULT_HPP

#include "../nostd/wstring.hpp"
#include "pawns/hero.hpp"

namespace Data {

/*
  A Result describes the aftermath of a single game. It stores the
  player's nickname, a reference to the Hero they used and their score (which
  must not be negative).
*/
class Result {
public:
  Result() = default;
  Result(const Nostd::WString &nickname, const Pawns::Hero *hero, int score);
  Result(Result &&) = default;
  Result &operator=(Result &&) = default;
  Result(const Result &) = default;
  Result &operator=(const Result &) = default;

  ~Result() = default;

  // getters
  const Nostd::WString &nickname() const noexcept;
  const Pawns::Hero *hero() const noexcept;
  int score() const noexcept;

  operator int() const; // converts results to scores (so they can be compared)

private:
  Nostd::WString nick{};
  const Pawns::Hero *hr{nullptr};
  int scr{0};
};

} // namespace Data

#endif
