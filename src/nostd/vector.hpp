#ifndef NOSTD_VECTOR_HPP
#define NOSTD_VECTOR_HPP
#include <stddef.h>
#include <stdexcept>

namespace Nostd {

template <typename V> class Vector {
private:
  V *v;
  size_t sz, cap;

public:
  // Constructs an empty container, with no elements.
  Vector() {
    sz = 0;
    cap = 1;
    v = new V[cap];
  }

  // it is constructor that creates a vector with size elements and size * 1.5
  // capacity
  explicit Vector(size_t size) {
    sz = size;
    if (size == 0)
      cap = 1;
    else if (size == 1)
      cap = 2;
    else
      cap = size * 1.5;
    v = new V[cap];
  }

  // Adds a new elements at the end of the vector
  void push_back(V ele) {
    if (sz == cap)
      resize(sz);
    v[sz++] = ele;
  }

  // Removes all elemennts from the vector
  void clear() { resize(0); };

  // Returns a reference to the element at position i in the vector
  V &at(size_t i) {
    if (i >= sz)
      throw std::invalid_argument("index out of bounds");
    return v[i];
  }

  // Removes from the vector either a single (or renge of) element
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

  // Resize the container so that it contains n elements
  void resize(size_t n) {
    sz = n;
    if (n == 0)
      cap = 1;
    else if (n == 1)
      cap = 2;
    else
      cap = n * 1.5;
    V *newv = new V[cap];
    for (size_t i = 0; i < n; i++)
      newv[i] = v[i];
    delete v;
    v = newv;
  }

  // returns the size of the array (length)
  size_t size() { return sz; }

  // returns the capactiy of the array (allocated size)
  size_t capacity() { return cap; }
};

} // namespace Nostd

#endif
