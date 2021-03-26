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

#include "allocator.hpp"
#include "concepts.hpp"
#include <algorithm>
#include <iterator>
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
  if (m != p.m || slc.start() != p.slc.start() || slc.size() != p.slc.size() ||
      slc.stride() != p.slc.stride() || ord != p.ord)
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
  return m == p.m && slc.start() == p.slc.start() &&
         slc.size() == p.slc.size() && slc.stride() == p.slc.stride() &&
         pstn == p.pstn && ord == p.ord;
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
    : all_elems{alloc}, all_exts{}, ord{extents.size()}, exts{nullptr} {
  sz = extents.size() ? 1UL : 0UL;
  if (sz) {
    exts = at_exts::allocate(all_exts, ord);
    size_t i{0};
    for (auto x : extents)
      sz *= (exts[i++] = x);
    elems = at_elems::allocate(all_elems, sz);
    for (pointer p{elems + sz - 1}; p >= elems; --p)
      at_elems::construct(all_elems, p, value);
  }
}

// move

template <class T, class Alloc>
Nostd::Matrix<T, Alloc>::Matrix(Matrix &&m)
    : all_elems{m.all_elems}, all_exts{m.all_exts}, ord{m.ord}, exts{m.exts},
      elems{m.elems}, sz{m.sz} {
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
  all_elems = m.all_elems;
  all_exts = m.all_exts;
  ord = m.ord;
  exts = m.exts;
  sz = m.sz;
  elems = m.elems;

  m.ord = m.sz = 0;
  m.exts = m.elems = nullptr;
  return *this;
}

// copy

template <class T, class Alloc>
Nostd::Matrix<T, Alloc>::Matrix(const Matrix &m, const allocator_type &alloc)
    : all_elems{alloc}, all_exts{}, ord{m.ord}, exts{nullptr}, sz{m.sz},
      elems{nullptr} {
  if (ord) {
    exts = at_exts::allocate(all_exts, ord);
    for (size_t i{0}; i < ord; ++i)
      exts[i] = m.exts[i];
    elems = at_elems::allocate(all_elems, sz);
    for (size_t i{0}; i < sz; ++i)
      elems[i] = m.elems[i];
  } else {
    exts = nullptr;
    elems = nullptr;
  }
}

template <class T, class Alloc>
Nostd::Matrix<T, Alloc>::Matrix(const Matrix &m) : Matrix(m, Alloc{}){};

template <class T, class Alloc>
auto Nostd::Matrix<T, Alloc>::Matrix::operator=(const Matrix &m) -> Matrix & {
  this->~Matrix();
  all_elems = m.all_elems;
  all_exts = m.all_exts;
  ord = m.ord;
  sz = m.sz;
  if (ord) {
    exts = at_exts::allocate(all_exts, ord);
    for (size_t i{0}; i < ord; ++i)
      exts[i] = m.exts[i];
    elems = at_elems::allocate(all_elems, sz);
    for (size_t i{0}; i < sz; ++i)
      elems[i] = m.elems[i];
  } else {
    exts = nullptr;
    elems = nullptr;
  }
}

template <class T, class Alloc> Nostd::Matrix<T, Alloc>::Matrix::~Matrix() {
  at_exts::deallocate(all_exts, exts, ord);
  pointer const end{elems + sz};
  for (pointer p{elems}; p < end; ++p)
    at_elems::destroy(all_elems, p);
  at_elems::deallocate(all_elems, elems, sz);
}

// iterators

template <class T, class Alloc>
auto Nostd::Matrix<T, Alloc>::Matrix::begin() noexcept -> iterator {
  return iterator(this, std::slice(0, exts[0], sz / exts[0]), 0, ord);
}

template <class T, class Alloc>
auto Nostd::Matrix<T, Alloc>::Matrix::begin() const noexcept -> const_iterator {
  return cbegin();
}

template <class T, class Alloc>
auto Nostd::Matrix<T, Alloc>::Matrix::end() noexcept -> iterator {
  return iterator(this, std::slice(0, exts[0], sz / exts[0]), exts[0], ord);
}

template <class T, class Alloc>
auto Nostd::Matrix<T, Alloc>::Matrix::end() const noexcept -> const_iterator {
  return cend();
}

template <class T, class Alloc>
auto Nostd::Matrix<T, Alloc>::Matrix::rbegin() noexcept -> reverse_iterator {
  return std::reverse_iterator<iterator>(begin());
}

template <class T, class Alloc>
auto Nostd::Matrix<T, Alloc>::Matrix::rbegin() const noexcept
    -> const_reverse_iterator {
  return crbegin();
}

template <class T, class Alloc>
auto Nostd::Matrix<T, Alloc>::Matrix::rend() noexcept -> reverse_iterator {
  return std::reverse_iterator<iterator>(end());
}

template <class T, class Alloc>
auto Nostd::Matrix<T, Alloc>::Matrix::rend() const noexcept
    -> const_reverse_iterator {
  return crend();
}

template <class T, class Alloc>
auto Nostd::Matrix<T, Alloc>::Matrix::cbegin() const noexcept
    -> const_iterator {
  return const_iterator(this, std::slice(0, exts[0], sz / exts[0]), 0, ord);
}

template <class T, class Alloc>
auto Nostd::Matrix<T, Alloc>::Matrix::cend() const noexcept -> const_iterator {
  return const_iterator(this, std::slice(0, exts[0], sz / exts[0]), exts[0],
                        ord);
}

template <class T, class Alloc>
auto Nostd::Matrix<T, Alloc>::Matrix::crbegin() const noexcept
    -> const_reverse_iterator {
  return const_reverse_iterator(this, std::slice(0, exts[0], sz / exts[0]), 0,
                                ord);
}

template <class T, class Alloc>
auto Nostd::Matrix<T, Alloc>::Matrix::crend() const noexcept
    -> const_reverse_iterator {
  return const_reverse_iterator(this, std::slice(0, exts[0], sz / exts[0]),
                                exts[0], ord);
}

// capacity

template <class T, class Alloc>
size_t Nostd::Matrix<T, Alloc>::Matrix::order() const noexcept {
  return ord;
}

template <class T, class Alloc>
size_t Nostd::Matrix<T, Alloc>::Matrix::extent(size_t n) const {
  if (n >= ord)
    throw std::out_of_range("n >= ord");
  return exts[n];
}

template <class T, class Alloc>
size_t Nostd::Matrix<T, Alloc>::Matrix::size() const noexcept {
  return sz;
}

template <class T, class Alloc>
bool Nostd::Matrix<T, Alloc>::Matrix::empty() const noexcept {
  return !sz;
}

template <class T, class Alloc>
auto Nostd::Matrix<T, Alloc>::Matrix::get_allocator() const noexcept
    -> allocator_type {
  return all_elems;
}

// elements access

template <class T, class Alloc>
auto Nostd::Matrix<T, Alloc>::Matrix::operator[](size_t n) -> iterator {
  return begin() + n;
}

template <class T, class Alloc>
auto Nostd::Matrix<T, Alloc>::Matrix::operator[](size_t n) const
    -> const_iterator {
  return cbegin() + n;
}

template <class T, class Alloc>
auto Nostd::Matrix<T, Alloc>::Matrix::at(size_t n) -> iterator {
  if (!ord)
    throw std::invalid_argument("!ord");
  if (n > exts[0])
    throw std::out_of_range("n > exts[0]");
  return (*this)[n];
}

template <class T, class Alloc>
auto Nostd::Matrix<T, Alloc>::Matrix::at(size_t n) const -> const_iterator {
  if (!ord)
    throw std::invalid_argument("!ord");
  if (n > exts[0])
    throw std::out_of_range("n > exts[0]");
  return (*this)[n];
}

template <class T, class Alloc>
auto Nostd::Matrix<T, Alloc>::Matrix::data() noexcept -> value_type * {
  return elems;
}

template <class T, class Alloc>
auto Nostd::Matrix<T, Alloc>::Matrix::data() const noexcept
    -> const value_type * {
  return elems;
}

// modifiers

template <class T, class Alloc>
void Nostd::Matrix<T, Alloc>::Matrix::fill(const value_type &value) {
  for (size_t i{0}; i < sz; ++i)
    elems[i] = value;
}

template <class T, class Alloc>
void Nostd::Matrix<T, Alloc>::Matrix::swap(Matrix &x) noexcept {
  std::swap(all_elems, x.all_elems);
  std::swap(all_exts, x.all_exts);
  std::swap(ord, x.ord);
  std::swap(exts, x.exts);
  std::swap(sz, x.sz);
  std::swap(elems, x.elems);
}

template <class T, class Alloc>
auto Nostd::Matrix<T, Alloc>::operator==(const Nostd::Matrix<T, Alloc> &m) ->
    typename std::enable_if<Has_equal<T>(), bool>::type {
  if (ord != m.ord)
    return false;
  for (size_t i{0}; i < m.ord; ++i)
    if (exts[i] != m.exts[i])
      return false;
  for (size_t i{0}; i < sz; ++i)
    if (elems[i] != m.elems[i])
      return false;
  return true;
}

template <class T, class Alloc>
auto Nostd::Matrix<T, Alloc>::operator!=(const Nostd::Matrix<T, Alloc> &m) ->
    typename std::enable_if<Has_equal<T>(), bool>::type {
  return !(*this == m);
}

#include "allocator.cpp"

#endif
