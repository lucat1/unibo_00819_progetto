#ifndef NOSTD_PAIR_HPP
#define NOSTD_PAIR_HPP

#include <ostream>

namespace Nostd {

template <typename A, typename B> class Pair {
public:
  A first;
  B second;

  Pair() = default;
  Pair(A first, B second) {
    this->first = first;
    this->second = second;
  }

  bool operator==(Pair<A, B> cmp) {
    return cmp.first == this->first && cmp.second == this->second;
  }
  bool operator!=(Pair<A, B> cmp) { return !operator==(cmp); }
};

template <typename A, typename B>
std::ostream &operator<<(std::ostream &os, const Pair<A, B> &pair) {
  return os << '(' << pair.first << ',' << pair.second << ')';
}

} // namespace Nostd

#endif // NOSTD_PAIR_HPP
