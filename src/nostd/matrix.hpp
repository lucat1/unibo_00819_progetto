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
#include <initializer_list>
#include <iterator>
#include <ostream>
#include <valarray>

#include "allocator.hpp"
#include "concepts.hpp"

namespace Nostd {

/*
  A general purpose class considering an N-dimensional matrix as a handler to
  its cells. To construct a new Matrix from scratch, you can specify its
  extents with {}.
*/
template <class T, class Alloc = Allocator<T>> class Matrix {
  static_assert(Regular<T>(), "Matrix's cell type is not regular");

public:
  template <class U> class Iterator;

  using value_type = T;
  using allocator_type = Alloc;
  using reference = value_type &;
  using const_reference = const value_type &;
  using pointer = value_type *;
  using const_pointer = const value_type *;
  using iterator = Iterator<value_type>;
  using const_iterator = Iterator<const value_type>;
  using reverse_iterator = std::reverse_iterator<Iterator<value_type>>;
  using const_reverse_iterator = std::reverse_iterator<const value_type>;
  using size_type = size_t;
  using difference_type = ptrdiff_t;

  /*
    A random access iterator able to point to any splice of a given Matrix. It
    can be used to access either a submatrix or a cell.
  */
  template <class U>
  class Iterator : public std::iterator<std::random_access_iterator_tag, U> {
    static_assert(Regular<U>(), "Matrix's cell type is not regular");

  public:
    Iterator() = default;
    Iterator(Matrix *, std::slice, size_t position, size_t order = 1);
    Iterator(const Iterator &) = default;
    Iterator &operator=(const Iterator &) = default;
    ~Iterator() = default;

    Iterator &operator++();
    Iterator operator++(int);
    Iterator &operator--();
    Iterator operator--(int);
    Iterator operator+(difference_type) const;
    Iterator operator-(difference_type) const;
    difference_type operator-(Iterator) const;
    Iterator &operator+=(difference_type);
    Iterator &operator-=(difference_type);

    bool operator==(const Iterator &) const noexcept;
    bool operator!=(const Iterator &) const noexcept;
    // the following operators throw a std::domain_error when comparing
    // submatrixes represented by different splices (for example, the ones
    // which do not have the same order). The same goes when calculating the
    // difference between two iterators.
    bool operator<(const Iterator &) const;
    bool operator>(const Iterator &) const;
    bool operator<=(const Iterator &) const;
    bool operator>=(const Iterator &) const;

    U &operator*() const;
    U *operator->() const;
    // p[n] is *not* the same as *(p + n): it returns an iterator pointing to
    // a submatrix of the one originally pointed. It throws std::out_of_range
    // on invalid submatrix indexes and std::domain_error when used on an
    // iterator pointing to a single cell.
    Iterator operator[](size_t) const;

    operator U &() const;

  private:
    Matrix *m{nullptr};
    std::slice slc;
    size_t pstn, ord, dim;
  };

  // extents are mandatory
  Matrix() = delete;
  Matrix(std::initializer_list<size_t> extents,
         const allocator_type &alloc = allocator_type());
  // fill in with the specified value
  Matrix(std::initializer_list<size_t> extents, const value_type &value,
         const allocator_type &alloc = allocator_type());

  // move
  Matrix(Matrix &&);
  Matrix(Matrix &&, const allocator_type &);
  Matrix &operator=(Matrix &&);

  // copy
  Matrix(const Matrix &);
  Matrix(const Matrix &, const allocator_type &alloc);
  Matrix &operator=(const Matrix &);

  ~Matrix();

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
  size_t extent(size_t) const;
  size_t size() const noexcept;
  bool empty() const noexcept;
  allocator_type get_allocator() const noexcept;

  // element access
  iterator operator[](size_t);
  const_iterator operator[](size_t) const;
  iterator at(size_type);
  const_iterator at(size_type) const;
  value_type *data() noexcept;
  const value_type *data() const noexcept;

  // modifiers
  void fill(const value_type &);
  void swap(Matrix &) noexcept; // this will invalid pre-swap iterators

private:
  using at_elems = std::allocator_traits<allocator_type>;
  using at_exts =
      std::allocator_traits<typename allocator_type::template other<size_t>>;

  allocator_type all;
  size_t ord, *exts, sz;
  pointer *elems;
};

// Two matrixes are said to be equal when they have same extents and elements.
template <class T, class Alloc>
std::enable_if<Has_equal<T>(), bool> operator==(const Matrix<T, Alloc> &,
                                                const Matrix<T, Alloc> &);
template <class T, class Alloc>
std::enable_if<Has_equal<T>(), bool> operator!=(const Matrix<T, Alloc> &,
                                                const Matrix<T, Alloc> &);

} // namespace Nostd

#endif
