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

#include <stdexcept>

template <class T, class Alloc>
template <class U>
Nostd::Matrix<T, Alloc>::Iterator<U>::Iterator(Matrix *matrix, size_t start,
                                               size_t size, size_t stride,
                                               size_t position)
    : m{matrix}, strt{start}, sz{size}, strd{stride}, pstn{position} {
  if (!m)
    throw std::invalid_argument("null matrix pointer");
  if (strt > m->size())
    throw std::out_of_range("strt > m->size()");
  if (!strd)
    throw std::invalid_argument("null stride");
  if (strt + sz * strd > m->size())
    throw std::out_of_range("strt + sz * strd > m->size()");
  if (pstn < strt)
    throw std::out_of_range("pstn < strt");
  if ((pstn - strt) % strd || (pstn - strt) / strd > size)
    throw std::out_of_range("misaligned position");
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
  if (-n * sz > pstn)
    throw std::out_of_range("-n * sz > pstn");
  return Iterator(m, strt, sz, strd, pstn + n * sz);
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
  if (m != p.m || strt != p.strt || sz != p.sz || strd != p.strd)
    throw std::invalid_argument("iterators working with different slices");
  return (static_cast<int>(pstn) - static_cast<int>(pstn)) / strd;
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
  return m == p.m && strt == p.strt && sz == p.sz && strd == p.strd &&
         pstn == p.pstn;
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
  if (pstn == strt + sz * strd)
    throw std::out_of_range("can't dereference end of sequence");
  return m->at(pstn);
}

template <class T, class Alloc>
template <class U>
U *Nostd::Matrix<T, Alloc>::Iterator<U>::operator->() const {
  if (pstn == strt + sz * strd)
    throw std::out_of_range("can't dereference end of sequence");
  return m;
}

template <class T, class Alloc>
template <class U>
auto Nostd::Matrix<T, Alloc>::Iterator<U>::operator[](size_t n) const
    -> Iterator {
  return *this; // TODO
}

#endif
