/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Luca Tagliavini #971133
  03/05/2021

  pair.hpp: defines and implements the Nostd::Pair class mimicking std::pair
*/
#ifndef NOSTD_PAIR_HPP
#define NOSTD_PAIR_HPP

#include <ostream>

namespace Nostd {

template <typename A, typename B> class Pair {
public:
  A first;
  B second;

  Pair() = delete;
  constexpr Pair(A first, B second) : first{first}, second{second} {}

  bool operator==(Pair<A, B> cmp) const {
    return cmp.first == this->first && cmp.second == this->second;
  }
  bool operator!=(Pair<A, B> cmp) const { return !operator==(cmp); }

  Pair<A, B> &operator=(const Pair<A, B> &other) {
    if (this == &other)
      return *this;
    this->first = other.first;
    this->second = other.second;
    return *this;
  }
};

template <typename A, typename B>
std::ostream &operator<<(std::ostream &os, const Pair<A, B> &pair) {
  return os << '(' << pair.first << ',' << pair.second << ')';
}

} // namespace Nostd

#endif // NOSTD_PAIR_HPP
