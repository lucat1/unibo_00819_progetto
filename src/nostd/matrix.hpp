/*
  University of Bologna
  First cicly degree in Computer Science
  00819 - Programmazione

  Stefano Volpe #969766
  03/16/2021

  matrix.hpp: user interface of Nostd::Matrix and its helper functions/classes.
*/

#ifndef NOSTD_MATRIX_HPP
#define NOSTD_MATRIX_HPP

#include <ostream>
#include <type_traits>
#include <valarray>
#include <vector>

namespace Nostd {

template <class T> class Matrix;
template <class T> class SubMatrix;

template <class T> class Matrix {
public:
  using value_type = T;
  using iterator = typename std::vector<T>::iterator;
  using const_iterator = typename std::vector<T>::const_iterator;

  Matrix() = default;
  Matrix(Matrix &&) = default;
  Matrix &operator=(Matrix &&) = default;
  Matrix(const Matrix &) = default;
  Matrix &operator=(const Matrix &) = default;
  ~Matrix() = default;

  Matrix(std::initializer_list<size_t>);
  Matrix &operator=(std::initializer_list<size_t>);

  size_t order() const noexcept;
  size_t extent(size_t n) const noexcept;
  size_t size() const noexcept;
  T *data() noexcept;
  const T *data() const noexcept;

private:
  std::vector<size_t> extents;
  std::vector<T> elems;
};

template <class T, size_t N, class C>
std::basic_ostream<C> &operator<<(std::basic_ostream<C> &, const Matrix<T> &);

} // namespace Nostd

#endif
