/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Stefano Volpe #969766
  03/16/2021

  matrix.hpp: user interface of Nostd::Matrix and its helper entities.
*/

#ifndef NOSTD_MATRIX_HPP
#define NOSTD_MATRIX_HPP

#include <cstddef>
#include <iterator>
#include <ostream>

#include "allocator.hpp"
#include "concepts.hpp"

namespace Nostd {

template <class T> class MatrixIterator;
template <class T, class Alloc> class Matrix;

/*
  A random access iterator able to point to any splice of a given Matrix. It
  can be used to access either a submatrix or a cell.
*/
template <class T> class MatrixIterator {
  static_assert(Regular<T>(), "Matrix's cell type is not regular");
  // TODO: satisfy std::random_access_iterator_tag
};

/*
  A general purpose class considering an N-dimensional matrix as a handler to
  its cells. To construct a new Matrix from scratch, you can specify its
  extents with {}: it can later be accessed through C-style subscripting (e.g.
  m[2][3]). All of these methods return a MatrixIterator pointing to a subset
  of the cells of the original data structure. A Matrix with a single cell ofù
  type T is implicitly converted to T.
  Finally, basic arithmetic operators are provided.
*/
template <class T, class Alloc = Allocator<T>> class Matrix {
  static_assert(Regular<T>(), "Matrix's cell type is not regular");

public:
  using value_type = T;
  using allocator_type = Alloc;
  using reference = value_type &;
  using const_reference = const value_type &;
  using pointer = value_type *;
  using const_pointer = const value_type *;
  using iterator = MatrixIterator<T>;
  using const_iterator = MatrixIterator<const value_type>;
  using reverse_iterator = std::reverse_iterator<MatrixIterator<value_type>>;
  using const_reverse_iterator = std::reverse_iterator<const value_type>;
  using size_type = size_t;
  using difference_type = ptrdiff_t;

  // extents are mandatory
  Matrix() = delete;
  Matrix(std::initializer_list<size_t> extents,
         const allocator_type &alloc = allocator_type());
  // fill in with the specified value
  Matrix(std::initializer_list<size_t> extents, const value_type &value,
         const allocator_type &alloc = allocator_type());

  // move
  Matrix(Matrix &&) = default;
  Matrix(Matrix &&, const allocator_type &alloc);
  Matrix &operator=(Matrix &&) = default;

  // copy
  Matrix(const Matrix &);
  Matrix(const Matrix &, const allocator_type &alloc);
  Matrix &operator=(const Matrix &);

  ~Matrix() = default;

  // iterators
  iterator begin() noexcept;
  const_iterator begin() const noexcept;
  iterator end() noexcept;
  const_iterator end() const noexcept;
  reverse_iterator rbegin() noexcept;
  const_reverse_iterator rbegin() const noexcept;
  reverse_iterator rend() noexcept;
  const_reverse_iterator rend() const noexcept;
  const_iterator cbegin() const noexcept;
  const_iterator cend() const noexcept;
  const_reverse_iterator crbegin() const noexcept;
  const_reverse_iterator crend() const noexcept;

  // capacity
  size_t order() const noexcept;
  size_t extent(size_t n) const;
  size_t size() const noexcept;
  bool empty() const noexcept;

  // element access
  iterator operator[](size_type);
  const_iterator operator[](size_type) const;
  iterator at(size_type);
  const_iterator at(size_type) const;
  reference front();
  const_reference front() const;
  reference back();
  const_reference back() const;
  value_type *data() noexcept;
  const value_type *data() const noexcept;

  // modifiers
  void fill(const value_type &);
  void swap(Matrix &x) noexcept;

private:
  size_t ord, *exts;
  T *elems;
};

// Two matrixes are said to be equal when they have same extents and elements.
template <class T, class Alloc>
std::enable_if<Has_equal<T>(), bool> operator==(const Matrix<T, Alloc> &,
                                                const Matrix<T, Alloc> &);
template <class T, class Alloc>
std::enable_if<Has_equal<T>(), bool> operator!=(const Matrix<T, Alloc> &,
                                                const Matrix<T, Alloc> &);

// Sends the string representation of a Matrix to a basic_ostream.
template <class T, class C>
std::enable_if<Streamable<T>, std::basic_ostream<C>> &
operator<<(std::basic_ostream<C> &, const Matrix<T> &);

} // namespace Nostd

#include "concepts.hpp"

#endif
