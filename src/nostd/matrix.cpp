/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Stefano Volpe #969766
  03/20/2021

  matrix.cpp: implementation of Nostd::Matrix and its helper entities.
*/

#ifndef NOSTD_MATRIX_CPP
#define NOSTD_MATRIX_CPP

#include "matrix.hpp"

#include <memory>
#include <stdexcept>

template <class T, class Alloc>
template <class U>
Nostd::Matrix<T, Alloc>::Iterator<U>::Iterator(Matrix *matrix, std::slice slice,
                                               size_t position, size_t order)
    : m{matrix}, slc{slice}, pstn{position}, ord{order} {
  if (m) {
    const size_t start{slc.start()}, matrix_size{m->size()};
    if (start > matrix_size)
      throw std::out_of_range("start > matrix_size");
    const size_t slice_size{slc.size()}, stride{slc.stride()};
    if (pstn < start)
      throw std::out_of_range("pstn < start");
    if ((pstn - start) % stride || (pstn - start) / stride > slice_size)
      throw std::out_of_range("misaligned position");
    const size_t matrix_order = m->order;
    if (order > matrix_order)
      throw std::out_of_range("order > matrix_order");
    dim = 1;
    for (size_t i{matrix_order - ord}; i < matrix_order; ++i)
      dim *= m->extent(i);
    if (slice_size && start + (slice_size - 1) * stride + dim > matrix_size)
      throw std::out_of_range("slice_size && start + (slice_size - 1) * stride "
                              "+ dim > matrix_size");
  }
}

template <class T, class Alloc>
template <class U>
auto Nostd::Matrix<T, Alloc>::Iterator<U>::operator++() -> Iterator & {
  return *this += 1;
}

template <class T, class Alloc>
template <class U>
auto Nostd::Matrix<T, Alloc>::Iterator<U>::operator++(int) -> Iterator {
  Iterator t{*this};
  ++*this;
  return t;
}

template <class T, class Alloc>
template <class U>
auto Nostd::Matrix<T, Alloc>::Iterator<U>::operator--() -> Iterator & {
  return *this -= 1;
}

template <class T, class Alloc>
template <class U>
auto Nostd::Matrix<T, Alloc>::Iterator<U>::operator--(int) -> Iterator {
  Iterator t{*this};
  --*this;
  return t;
}

template <class T, class Alloc>
template <class U>
auto Nostd::Matrix<T, Alloc>::Iterator<U>::operator+(difference_type n) const
    -> Iterator {
  const size_t stride{slc.stride()};
  if (-n * stride > pstn)
    throw std::out_of_range("-n * stride > pstn");
  return Iterator(m, slc, pstn + n * stride, ord);
}

template <class T, class Alloc>
template <class U>
auto Nostd::Matrix<T, Alloc>::Iterator<U>::operator-(difference_type n) const
    -> Iterator {
  return *this + (-n);
}

template <class T, class Alloc>
template <class U>
auto Nostd::Matrix<T, Alloc>::Iterator<U>::operator-(Iterator p) const
    -> difference_type {
  if (m != p.m || slc != p.slc || ord != p.ord)
    throw std::invalid_argument("iterators working with different slices");
  return (static_cast<int>(pstn) - static_cast<int>(p.pstn)) / slc.stride();
}

template <class T, class Alloc>
template <class U>
auto Nostd::Matrix<T, Alloc>::Iterator<U>::operator+=(difference_type n)
    -> Iterator & {
  pstn = pstn + n;
  return *this;
}

template <class T, class Alloc>
template <class U>
auto Nostd::Matrix<T, Alloc>::Iterator<U>::operator-=(difference_type n)
    -> Iterator & {
  return *this += -n;
}

template <class T, class Alloc>
template <class U>
bool Nostd::Matrix<T, Alloc>::Iterator<U>::operator==(
    const Iterator &p) const noexcept {
  // every field is compared, so this is actually a memberwise comparison
  return m == p.m && slc == p.slc && pstn == p.pstn && ord == p.ord;
}

template <class T, class Alloc>
template <class U>
bool Nostd::Matrix<T, Alloc>::Iterator<U>::operator!=(
    const Iterator &p) const noexcept {
  return !(*this == p);
}

template <class T, class Alloc>
template <class U>
bool Nostd::Matrix<T, Alloc>::Iterator<U>::operator<(const Iterator &p) const {
  return *this - p < 0;
}

template <class T, class Alloc>
template <class U>
bool Nostd::Matrix<T, Alloc>::Iterator<U>::operator>(const Iterator &p) const {
  return *this - p > 0;
}

template <class T, class Alloc>
template <class U>
bool Nostd::Matrix<T, Alloc>::Iterator<U>::operator<=(const Iterator &p) const {
  return !(*this > p);
}

template <class T, class Alloc>
template <class U>
bool Nostd::Matrix<T, Alloc>::Iterator<U>::operator>=(const Iterator &p) const {
  return !(*this < p);
}

template <class T, class Alloc>
template <class U>
U &Nostd::Matrix<T, Alloc>::Iterator<U>::operator*() const {
  if (pstn == slc.start() + slc.size() * slc.stride())
    throw std::out_of_range("can't dereference end of sequence");
  return m->at(pstn);
}

template <class T, class Alloc>
template <class U>
U *Nostd::Matrix<T, Alloc>::Iterator<U>::operator->() const {
  if (pstn == slc.start() + slc.size() * slc.stride())
    throw std::out_of_range("can't dereference end of sequence");
  return m;
}

template <class T, class Alloc>
template <class U>
auto Nostd::Matrix<T, Alloc>::Iterator<U>::operator[](size_t n) const
    -> Iterator {
  if (!ord)
    throw std::invalid_argument("using [] on a 0-order matrix");
  const size_t size{m->extent(m->order() - ord)};
  if (n >= size)
    throw std::out_of_range("n >= size");
  return Iterator(m,
                  std::slice(slc.start() + n * slc.stride(), size, dim / size),
                  slc.start(), ord - 1);
}

template <class T, class Alloc>
template <class U>
Nostd::Matrix<T, Alloc>::Iterator<U>::operator U &() const {
  return **this;
}

template <class T, class Alloc>
Nostd::Matrix<T, Alloc>::Matrix(std::initializer_list<size_t> extents,
                                const allocator_type &alloc)
    : Matrix(extents, value_type{}, alloc) {}

template <class T, class Alloc>
Nostd::Matrix<T, Alloc>::Matrix(std::initializer_list<size_t> extents,
                                const value_type &value,
                                const allocator_type &alloc)
    : all{alloc}, ord{extents.size()}, exts{all.allocate(extents.size())} {
  sz = extents.size() ? 1UL : 0UL;
  if (sz) {
    using at = std::allocator_traits<allocator_type>;
    exts = at::allocate(ord);
    size_t i{0};
    for (auto x : extents)
      sz *= (exts[i++] = x);
    elems = at::allocate(sz);
    for (pointer p{elems + sz - 1}; p >= elems; --p)
      at::construct(p, value);
  }
}

template <class T, class Alloc>
Nostd::Matrix<T, Alloc>::Matrix(Matrix &&m)
    : all{m.all}, ord{m.ord}, exts{m.exts}, elems{m.elems}, sz{m.sz} {
  m.ord = 0;
  m.exts = m.elems = nullptr;
}

template <class T, class Alloc>
Nostd::Matrix<T, Alloc>::Matrix(Matrix &&m, const allocator_type &alloc) {
  if (alloc == m.all)
    *this = Matrix(m);
  else {
    const Matrix &n{m};
    *this = Matrix(n, alloc);
  }
}

template <class T, class Alloc>
auto Nostd::Matrix<T, Alloc>::Matrix::operator=(Matrix &&m) -> Matrix & {
  this->~Matrix();
  all = m.all;
  ord = m.ord;
  exts = m.exts;
  sz = m.sz;
  elems = m.elems;

  m.ord = m.sz = 0;
  m.exts = m.elems = nullptr;
  return *this;
}

template <class T, class Alloc>
Nostd::Matrix<T, Alloc>::Matrix(const Matrix &m, const allocator_type &alloc)
    : all{alloc}, ord{m.ord}, sz{m.sz} {
  if (ord) {
    using at = std::allocator_traits<allocator_type>;
    exts = at::allocate(ord);
    for (size_t i{0}; i < ord; ++i)
      exts[i] = m.exts[i];
    elems = at::allocate(sz);
    for (size_t i{0}; i < sz; ++i)
      elems[i] = m.elems[i];
  } else
    exts = elems = nullptr;
}

template <class T, class Alloc>
Nostd::Matrix<T, Alloc>::Matrix(const Matrix &m) : Matrix(m, Alloc{}){};

template <class T, class Alloc>
auto Nostd::Matrix<T, Alloc>::Matrix::operator=(const Matrix &m) -> Matrix & {
  this->~Matrix();
  all = m.all;
  ord = m.ord;
  sz = m.sz;
  if (ord) {
    using at = std::allocator_traits<allocator_type>;
    exts = at::allocate(ord);
    for (size_t i{0}; i < ord; ++i)
      exts[i] = m.exts[i];
    elems = at::allocate(sz);
    for (size_t i{0}; i < sz; ++i)
      elems[i] = m.elems[i];
  } else
    exts = elems = nullptr;
}

template <class T, class Alloc> Nostd::Matrix<T, Alloc>::Matrix::~Matrix() {
  using at = std::allocator_traits<allocator_type>;
  at::deallocate(exts, ord);
  pointer const end{elems + sz};
  for (pointer p{elems}; p < end; ++p)
    at::destroy(p);
  at::deallocate(elems, sz);
}

#endif
