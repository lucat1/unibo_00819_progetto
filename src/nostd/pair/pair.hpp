#ifndef PAIR_HPP
#define PAIR_HPP

namespace Nostd {

template <typename A, typename B> class Pair {
public:
  A first;
  B second;

  Pair(A first, B second) {
    this->first = first;
    this->second = second;
  }

  bool operator==(Pair<A, B> cmp) {
    return cmp.first == this->first && cmp.second == this->second;
  }
  bool operator!=(Pair<A, B> cmp) { return !operator==(cmp); }
};

} // namespace Nostd

#endif // PAIR_HPP
