#ifndef NOSTD_VECTOR_HPP
#define NOSTD_VECTOR_HPP

#include "allocator.hpp"
#include <algorithm>
#include <iterator>
#include <stdexcept>

namespace Nostd {

template <typename V, class Alloc = Allocator<V>> class Vector {
public:
  using allocator_type = Alloc;
  using iterator = V *;
  using reverse_iterator = std::reverse_iterator<iterator>;
  using const_iterator = const V *;
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;

protected:
  allocator_type all_elems;
  V *v = nullptr;
  size_t sz = 0, cap = 0;

  void calc_cap() {
    if (sz == 0)
      cap = 1;
    else if (sz == 1)
      cap = 2;
    else
      cap = sz * 1.5;
  }

  void allocate_v(size_t size) {
    sz = size;
    calc_cap();
    v = all_elems.allocate(cap);
  }

  void construct_v(size_t size, const V &ele) {
    for (size_t i = 0; i < size; i++)
      all_elems.construct(v + i, ele);
  }

  void shrink(size_t size) {
    if (size < sz) {
      size_t old_cap = cap;
      sz = size;
      calc_cap();
      V *newv = all_elems.allocate(cap);
      for (size_t i = 0; i < sz; ++i)
        all_elems.construct(newv + i, v[i]);
      all_elems.deallocate(v, old_cap);
      v = newv;
    }
  }

public:
  // Constructs an empty container, with no elements.
  Vector(const allocator_type &alloc = allocator_type()) {
    all_elems = alloc;
    allocate_v(0);
  }
  // Constructs a vector of the given size
  explicit Vector(size_t size, const allocator_type &alloc = allocator_type()) {
    all_elems = alloc;
    allocate_v(size);
  }
  // it is constructor that creates a vector with size elements and size * 1.5
  // capacity copying size times the ele value into the vector
  Vector(size_t size, const V &ele,
         const allocator_type &alloc = allocator_type()) {
    all_elems = alloc;
    allocate_v(size);
    construct_v(size, ele);
  }
  // Copies data from another vector instance (in linear time)
  Vector(const Vector &vec, const allocator_type &alloc = allocator_type()) {
    all_elems = alloc;
    allocate_v(vec.sz);
    for (size_t i = 0; i < vec.sz; i++)
      all_elems.construct(v + i, vec[i]);
  }
  // Moves data from another vector (resues same memory sequence for v)
  Vector(Vector &&vec, const allocator_type &alloc = allocator_type()) {
    all_elems = alloc;
    this->v = vec.v;
    this->sz = vec.sz;
    this->cap = vec.cap;
    vec.v = nullptr; // to prevent unwanted deallocations
  }
  ~Vector() {
    all_elems.deallocate(v, cap);
    v = nullptr;
  }

  // Adds a new element at the end of the vector
  void push_back(V ele) {
    if (sz == cap)
      resize(sz + 1, ele);
    else
      all_elems.construct(v + sz++, ele);
  }

  // Removes all elemennts from the vector
  void clear() { shrink(0); };

  // Returns a reference to the element at position i in the vector
  V &at(size_t i) {
    if (i >= sz)
      throw std::out_of_range("index out of bounds");
    return v[i];
  }

  // Returns a constant reference to the element at index i
  const V &at(size_t i) const {
    if (i >= sz)
      throw std::out_of_range("index out of bounds");
    return v[i];
  }

  // Reference "at" operator. NOTE: throws unlike C++'s
  V &operator[](size_t i) { return at(i); }

  // Cconstant "at" operator reference. NOTE: throws unlike C++'s
  const V &operator[](size_t i) const { return at(i); };

  // Copy assignment operator
  Vector<V> &operator=(const Vector<V> &vec) {
    this->~Vector();
    sz = vec.size();
    calc_cap();

    V *newv = all_elems.allocate(cap);
    for (size_t i = 0; i < sz; i++)
      all_elems.construct(newv + i, vec[i]);
    v = newv;
    return *this;
  }

  // Move assigment operator
  Vector<V> &operator=(Vector<V> &&vec) {
    all_elems.deallocate(v, cap);
    all_elems = vec.all_elems;
    v = vec.v;
    sz = vec.sz;
    cap = vec.cap;
    vec.v = nullptr; // to prevent unwanted deallocations
    return *this;
  }

  // Removes a signle item from the vector
  size_t erase(size_t i) {
    if (i >= sz)
      throw std::out_of_range("index out of bounds");
    all_elems.destroy(v + i);
    for (size_t k = i; k < sz - 1; k++)
      v[k] = v[k + 1];

    if (sz >= cap * 2 / 3)
      sz = sz - 1;
    else
      shrink(sz - 1);

    return i;
  }

  // Resize the container so that it contain n elements
  void resize(size_t n, V val = V()) {
    size_t old_sz = sz, old_cap = cap, n_copies = std::min(n, sz);
    sz = n;
    calc_cap();

    V *newv = all_elems.allocate(cap);
    // copy old values
    for (size_t i = 0; i < n_copies; i++)
      all_elems.construct(newv + i, v[i]);
    // initialize new values (n > old_sz)
    for (size_t i = old_sz; i < sz; i++)
      all_elems.construct(newv + i, val);
    all_elems.deallocate(v, old_cap);
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

} // namespace Nostd

#include "allocator.cpp"

#endif // NOSTD_VECTOR_HPP
