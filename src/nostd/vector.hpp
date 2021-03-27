#ifndef NOSTD_VECTOR_HPP
#define NOSTD_VECTOR_HPP
#include <stddef.h>
#include <stdexcept>

namespace Nostd {

template <typename V> class Vector {
protected:
  V *v;
  size_t sz, cap;

  void calc_cap() {
    if (sz == 0)
      cap = 1;
    else if (sz == 1)
      cap = 2;
    else
      cap = sz * 1.5;
  }

  void init_v(size_t size) {
    sz = size;
    calc_cap();
    v = new V[cap];
  }

public:
  // Constructs an empty container, with no elements.
  Vector() { init_v(0); }
  // Constructs a vector of the given size
  explicit Vector(size_t size) { init_v(size); }
  // it is constructor that creates a vector with size elements and size * 1.5
  // capacity copying size times the ele value into the vector
  Vector(size_t size, V ele) {
    init_v(size);
    for (size_t i = 0; i < sz; i++)
      v[i] = ele;
  }
  // Copies from another vector instance
  Vector(Vector &&v) {
    this->v = v->v;
    this->sz = v->sz;
    this->cap = v->cap;
    v->v = nullptr; // to preven unwanted deallocations
  }
  ~Vector() { delete[] v; }

  // Adds a new element at the end of the vector
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
      throw std::out_of_range("index out of bounds");
    return v[i];
  }

  V &operator[](size_t i) { return at(i); }

  // Removes a signle item from the vector
  size_t erase(size_t i) {
    if (i >= sz)
      throw std::out_of_range("index out of bounds");

    for (size_t k = i; k < sz - 1; k++)
      v[k] = v[k + 1];

    if (sz >= cap * 2 / 3)
      sz = sz - 1;
    else
      resize(sz - 1);

    return i;
  }

  // Resize the container so that it contain n elements
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
    delete[] v;
    v = newv;
  }

  // returns the size of the array (length)
  size_t size() { return sz; }

  // returns the capactiy of the array (allocated size)
  size_t capacity() { return cap; }

  // returns wheter the vector is empty or not
  bool empty() { return sz == 0; }
};

} // namespace Nostd

#endif // NOSTD_VECTOR_HPP
