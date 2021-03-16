#ifndef NOSTD_VECTOR_HPP
#define NOSTD_VECTOR_HPP
#include <stddef.h>

namespace Nostd {
template <typename V>
class Vector {
 private:
  V* v;
  size_t sz, cap;

 public:
  Vector() {
    sz = 0;
    cap = 1;
    v = new V[cap];
  }
  explicit Vector(size_t size) {
    sz = size;
    if (size == 0)
      cap = 1;
    else
      cap = size * 1.5;
    v = new V[cap];
  }
  void push_back(V ele) {
    if (sz == cap)
      resize(sz);
    v[sz++] = ele;
  }
  void clear() { resize(0); };
  V& at(size_t i) {
    if (i >= sz)
      throw std::invalid_argument("index out of bounds");
    return v[i];
  }
  size_t erase(size_t i) {
    if (i >= sz)
      throw std::invalid_argument("index out of bounds");

    for (size_t k = i; k < sz - 1; k++)
      v[k] = v[k + 1];

    if (sz >= cap * 2 / 3)
      sz = sz - 1;
    else
      resize(sz - 1);

    return i;
  }
  void resize(size_t n) {
    sz = n;
    if (n == 0)
      cap = 1;
    else
      cap = n * 1.5;
    V* newv = new V[cap];
    for (size_t i = 0; i < n; i++)
      newv[i] = v[i];
    delete v;
    v = newv;
  }
  size_t size() { return sz; }
  size_t capacity() { return cap; }
};
}  // namespace Nostd

#endif