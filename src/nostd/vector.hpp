#ifndef NOSTD_VECTOR_HPP
#define NOSTD_VECTOR_HPP
#include <iterator>
#include <stdexcept>

namespace Nostd {

template <typename V>
class Vector {
 public:
  using iterator = V*;
  using reverse_iterator = std::reverse_iterator<iterator>;
  using const_iterator = const V*;
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;

 protected:
  V* v;
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
    v = reinterpret_cast<V*>(::operator new(cap * sizeof(V)));
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
  // Copies data from another vector instance (in linear time)
  Vector(Vector& vec) {
    init_v(vec.sz);
    for (size_t i = 0; i < vec.sz; i++)
      this->v[i] = vec[i];
  }
  // Moves data from another vector (resues same memory sequence for v)
  Vector(Vector&& vec) {
    this->v = vec.v;
    this->sz = vec.sz;
    this->cap = vec.cap;
    vec.v = nullptr;  // to prevent unwanted deallocations
  }
  ~Vector() { ::operator delete(v); }

  // Adds a new element at the end of the vector
  void push_back(V ele) {
    if (sz == cap)
      resize(sz);
    v[sz++] = ele;
  }

  // Removes all elemennts from the vector
  void clear() { resize(0); };

  // Returns a reference to the element at position i in the vector
  V& at(size_t i) {
    if (i >= sz)
      throw std::out_of_range("index out of bounds");
    return v[i];
  }

  const V& at(size_t i) const {
    if (i >= sz)
      throw std::out_of_range("index out of bounds");
    return v[i];
  }

  V& operator[](size_t i) { return at(i); }

  const V& operator[](size_t i) const { return at(i); };

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
    V* newv = reinterpret_cast<V*>(::operator new((cap + 1) * sizeof(V)));
    for (size_t i = 0; i < n; i++)
      newv[i] = v[i];
    ::operator delete(v);
    v = newv;
  }

  // returns whether the vector is empty
  bool empty() const { return sz == 0; };
  // returns the size of the array (length)
  size_t size() const { return sz; }
  // returns the capactiy of the array (allocated size)
  size_t capacity() const { return cap; }

  iterator begin() { return &v[0]; }
  const_iterator begin() const { return &v[0]; }
  iterator end() { return &v[sz - 1] + 1; }
  const_iterator end() const { return &v[sz - 1] + 1; }
  reverse_iterator rbegin() { return reverse_iterator(end() - 1); }
  reverse_iterator rend() { return reverse_iterator(begin() - 1); }
  const_iterator cbegin() const { return &v[0]; }
  const_iterator cend() const { return &v[sz - 1] + 1; }
  const_reverse_iterator crbegin() const {
    return const_reverse_iterator(end() - 1);
  }
  const_reverse_iterator crend() const {
    return const_reverse_iterator(begin() - 1);
  }
};

}  // namespace Nostd

#endif  // NOSTD_VECTOR_HPP
