/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Stefano Volpe #969766
  03/17/2021

  allocator.cpp: implementation of Nostd::Allocator.
*/

#ifndef NOSTD_ALLOCATOR_CPP
#define NOSTD_ALLOCATOR_CPP

#include "allocator.hpp"

#include <limits>

template <class T>
template <class U>
Nostd::Allocator<T>::Allocator(const Allocator<U> &) noexcept {}

template <class T>
auto Nostd::Allocator<T>::address(reference x) const noexcept -> pointer {
  return &x;
}

template <class T>
auto Nostd::Allocator<T>::address(const_reference x) const noexcept
    -> const_pointer {
  return &x;
}

template <class T>
auto Nostd::Allocator<T>::allocate(size_type n, Allocator<void>::const_pointer)
    -> pointer {
  return ::operator new(n * sizeof(value_type));
}

template <class T> void Nostd::Allocator<T>::deallocate(pointer p, size_type) {
  ::operator delete(p);
}

template <class T>
auto Nostd::Allocator<T>::max_size() const noexcept -> size_type {
  return std::numeric_limits<size_type>::max() / sizeof(T);
}

template <class T>
template <class U, class... Args>
void Nostd::Allocator<T>::construct(U *p, Args &&...args) {
  ::new (p) U{args...};
}

template <class T> template <class U> void Nostd::Allocator<T>::destroy(U *p) {
  p->~U();
}

#endif
