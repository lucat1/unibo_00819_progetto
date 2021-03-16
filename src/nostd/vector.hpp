#ifndef NOSTD_VECTOR_HPP
#define NOSTD_VECTOR_HPP
#include <stddef.h>

namespace Nostd {
template <typename V>
class Vector {
  // The class members declared as private ca be accessed only by
  // the function inside the class
 private:
  V* v;
  size_t sz, cap;

 public:
  // All the class members declared under public will be available to
  // everyone
  Vector() {
    // Constructs an empty container, with no elements.
    sz = 0;
    cap = 1;
    v = new V[cap];
  }

  explicit Vector(size_t size) {
    // it is constructor that creates a vector with size elements and size * 1.5
    // capacity
    sz = size;
    if (size == 0)
      cap = 1;
    else
      cap = size * 1.5;
    v = new V[cap];
  }

  void push_back(V ele) {  // Adds a new elements at the end of the vector
    if (sz == cap)
      resize(sz);
    v[sz++] = ele;
  }

  void clear() { resize(0); };  // Removes all elemennts from the vector

  V& at(size_t i) {
    // Returns a reference to the element at position i in the
    // vector
    if (i >= sz)
      throw std::invalid_argument("index out of bounds");
    return v[i];
  }

  size_t erase(size_t i) {
    // Removes from the vector either a single (or renge
    // of) element
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
    // Resize the container so that it contains n
    // elements
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

  size_t size() {
    return sz;
  }  // It's a type able ro represent the size of any object

  size_t capacity() { return cap; }
};
}  // namespace Nostd

#endif