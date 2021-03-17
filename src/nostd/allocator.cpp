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

#endif
