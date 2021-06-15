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
  Result(const Nostd::WString &, int, Engine::Color, wchar_t);
  Result(Result &&) = default;
  Result &operator=(Result &&) = default;
  Result(const Result &) = default;
  Result &operator=(const Result &) = default;

  ~Result() = default;

  // getters
  const Nostd::WString &name() const noexcept override;
  int score() const noexcept;
  Engine::Color foreground() const noexcept override;
  wchar_t character() const noexcept override;

  operator int() const; // converts results to scores (so they can be compared)

private:
  Nostd::WString nm{};
  int scr{0};
  Engine::Color fg{Engine::Color::transparent};
  wchar_t chr{L' '};
};

} // namespace Pawns

} // namespace Data

#endif
