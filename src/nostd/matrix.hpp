/*
  University of Bologna
  First cicly degree in Computer Science
  00819 - Programmazione

  Stefano Volpe #969766
  03/16/2021

  matrix.hpp: user interface of Nostd::Matrix and its helper functions.
*/

#ifndef NOSTD_MATRIX_HPP
#define NOSTD_MATRIX_HPP

#include <iterator>
#include <ostream>
#include <utility>
#include <vector>

namespace Nostd {

/*
  A general purpose class considering an N-dimensional matrix as a handler to
  its cells. To construct a new Matrix from scratch, you can specify its
  extents with {}: it can later be accessed through C-style subscripting (e.g.
  m[2][3]) or using intervals (m[{{2,3}, {1,1}]). All of these methods return
  a new handler of type Matrix pointing to a subset of the cells of the
  original data structure. A Matrix with a single cell of type T is implicitly
  converted to T.
  Finally, basic arithmetic operators are provided.
*/
template <class T, class Alloc = allocator<T>> class Matrix {
public:
  using value_type = T;
  using allocator_type = Alloc;
  using reference = value_type &;
  using const_reference = const value_type &;
  using pointer = value_type *;
  using const_pointer = const value_type *;
  using iterator = typename std::vector<T>::iterator;
  using const_iterator = typename std::vector<T>::const_iterator;
  using reverse_iterator = std::reverse_iterator<iterator>;
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;
  using size_type = size_t;

  Matrix() = delete;
  Matrix(Matrix &&) = default;
  Matrix &operator=(Matrix &&) = default;
  Matrix(const Matrix &);
  Matrix &operator=(const Matrix &);
  ~Matrix() = default;

  Matrix(std::initializer_list<size_t> extents);
  Matrix(std::initializer_list<size_t> extents, const T &value);
  Matrix &operator=(std::initializer_list<size_t> extents);

  // Retrieve data/references
  size_t order() const noexcept;
  size_t extent(size_t n) const noexcept;
  size_t size() const noexcept;
  T *data() noexcept;
  const T *data() const noexcept;
  const Matrix &operator[](size_t) const;
  Matrix &operator[](size_t);
  const Matrix &
  operator[](std::initializer_list<std::pair<size_t, size_t>>) const;
  Matrix &operator[](std::initializer_list<std::pair<size_t, size_t>>);
  operator T &();
  operator const T &() const;

  // Basic arithmetic
  Matrix &operator=(const T &);
  bool operator==(const Matrix &) const;
  bool operator!=(const Matrix &) const;

private:
  size_t start;
  std::vector<size_t> extents, strides;
  std::vector<T> *elems;
};

// Sends the string representation of a Matrix to a basic_ostream.
template <class T, size_t N, class C>
std::basic_ostream<C> &operator<<(std::basic_ostream<C> &, const Matrix<T> &);

} // namespace Nostd

#endif
