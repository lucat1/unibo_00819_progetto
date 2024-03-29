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

#include <initializer_list>
#include <iterator>
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
  class Iterator;
  class ConstIterator;

  using value_type = T;
  using allocator_type = Alloc;
  using reference = value_type &;
  using const_reference = const value_type &;
  using pointer = value_type *;
  using const_pointer = const value_type *;
  using iterator = Iterator;
  using const_iterator = ConstIterator;
  using reverse_iterator = std::reverse_iterator<iterator>;
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;
  using size_type = size_t;
  using difference_type = ptrdiff_t;

  /*
    A random access iterator able to point to any splice of a given Matrix. It
    can be used to access either a submatrix or a cell.
  */
  class ConstIterator
      : public std::iterator<std::random_access_iterator_tag, value_type> {

  public:
    ConstIterator() = default;
    ConstIterator(const Matrix *, std::slice, size_t position,
                  size_t order = 1);
    ConstIterator(const ConstIterator &) = default;
    ConstIterator &operator=(const ConstIterator &) = default;
    ~ConstIterator() = default;

    // iterators
    ConstIterator begin() const noexcept; // iterator to the first row
    ConstIterator end() const noexcept;   // iterator to the row after the last

    ConstIterator &operator++();
    ConstIterator operator++(int);
    ConstIterator &operator--();
    ConstIterator operator--(int);
    ConstIterator operator+(difference_type) const;
    ConstIterator operator-(difference_type) const;
    difference_type operator-(ConstIterator) const;
    ConstIterator &operator+=(difference_type);
    ConstIterator &operator-=(difference_type);

    bool operator==(const ConstIterator &) const noexcept;
    bool operator!=(const ConstIterator &) const noexcept;
    // The following operators throw a std::domain_error when comparing
    // submatrixes represented by different splices (for example, the ones
    // which do not have the same order). The same goes when calculating the
    // difference between two iterators.
    bool operator<(const ConstIterator &) const;
    bool operator>(const ConstIterator &) const;
    bool operator<=(const ConstIterator &) const;
    bool operator>=(const ConstIterator &) const;

    // As a submatrix cannot be dereferenced to a single value, *p must return
    // p itself. This is still useful in for-each loops, but please remember:
    // if you work with a copy of the iterator, you are still working on the
    // same matrix.
    ConstIterator &operator*();
    ConstIterator *operator->();
    // p[n] is *not* the same as *(p + n): it returns an iterator pointing to
    // a submatrix of the one originally pointed. An at() method is also
    // available: it throws std::out_of_range on invalid submatrix indexes and
    // std::domain_error when used on an iterator pointing to a single cell.
    ConstIterator operator[](size_t) const noexcept;
    ConstIterator at(size_t) const;

    // Returns a reference to the pointed value: use instead of *
    const_reference value() const;

  protected: // very bad
    const Matrix *m{nullptr};
    std::slice slc;
    size_t pstn, ord, dim;
  };

  class Iterator : public ConstIterator {
  public:
    Iterator() = default;
    Iterator(Matrix *, std::slice, size_t position, size_t order = 1);

    Iterator begin() const noexcept; // iterator to the first row
    Iterator end() const noexcept;   // iterator to the row after the last

    Iterator &operator++();
    Iterator operator++(int);
    Iterator &operator--();
    Iterator operator--(int);
    Iterator operator+(difference_type) const;
    Iterator operator-(difference_type) const;
    Iterator &operator+=(difference_type);
    Iterator &operator-=(difference_type);

    // As a submatrix cannot be dereferenced to a single value, *p must return
    // p itself. This is still useful in for-each loops, but please remember:
    // if you work with a copy of the iterator, you are still working on the
    // same matrix.
    Iterator &operator*();
    Iterator *operator->();
    // p[n] is *not* the same as *(p + n): it returns an iterator pointing to
    // a submatrix of the one originally pointed. An at() method is also
    // available: it throws std::out_of_range on invalid submatrix indexes and
    // std::domain_error when used on an iterator pointing to a single cell.
    Iterator operator[](size_t) const noexcept;
    Iterator at(size_t) const;

    // Returns a reference to the pointed value: use instead of *
    reference value() const;

  private:
    Matrix *m_{nullptr};
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
  iterator begin() noexcept; // iterator referring to the first row
  const_iterator begin() const noexcept;
  iterator end() noexcept; // iterator referring to the row after the last
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
  size_t order() const noexcept;               // number of dimensions
  size_t extent(size_t dimension_index) const; // getter for any extent
  size_t size() const noexcept;                // the total number of elements
  bool empty() const noexcept; // checks whether the matrix is empty
  allocator_type get_allocator() const noexcept; // returns the allocator used

  // element access
  iterator operator[](size_t); // access to an indexed row
  const_iterator operator[](size_t) const;
  iterator at(size_type); // like [], but with checked bounds
  const_iterator at(size_type) const;
  pointer data() noexcept; // access to the C-style array
  const_pointer data() const noexcept;

  // modifiers
  void fill(const_reference);   // sets every element to the given value
  void swap(Matrix &) noexcept; // this will invalid pre-swap iterators

  // Two matrixes are said to be equal when they have same extents and elements.
  typename std::enable_if<Has_equal<T>(), bool>::type
  operator==(const Matrix<T, Alloc> &);

  typename std::enable_if<Has_equal<T>(), bool>::type
  operator!=(const Matrix<T, Alloc> &);

private:
  using at_elems = std::allocator_traits<allocator_type>;
  using at_exts =
      std::allocator_traits<typename allocator_type::template other<size_t>>;

  allocator_type all_elems;
  typename at_exts::allocator_type all_exts;
  size_t ord, *exts, sz;
  pointer elems;
};

} // namespace Nostd

#endif
