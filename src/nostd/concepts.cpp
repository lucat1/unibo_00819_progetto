/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Stefano Volpe #969766
  03/19/2021

  concepts.cpp: implementation of generic programming concepts (which will be
  introduced as an actual language facility only in C++20)
*/

#ifndef NOSTD_CONCEPTS_CPP
#define NOSTD_CONCEPTS_CPP

#include "concepts_impl.hpp"

#include <type_traits>

using namespace Nostd;

template <class T> constexpr bool Nostd::Has_equal() {
  return Has_equal_trait<T>::value;
}

template <class T> constexpr bool Nostd::Has_not_equal() {
  return Has_not_equal_trait<T>::value;
}

template <class T> constexpr bool Nostd::Has_right_shift() {
  return Has_right_shift_trait<T>::value;
}

template <class T> constexpr bool Nostd::Has_left_shift() {
  return Has_left_shift_trait<T>::value;
}

template <class T> constexpr bool Nostd::Boolean() {
  return std::is_convertible<T, bool>();
}

template <class T> constexpr bool Nostd::Equality_comparable() {
  return Has_equal<T>() && Boolean<Equal_result<T>::type> &&
         Has_not_equal<T>() && Boolean<Not_equal_result<T>::type>;
}

template <class T> constexpr bool Nostd::Movable() {
  return std::is_move_constructible<T>() && std::is_move_assignable<T>();
}

template <class T> constexpr bool Nostd::Copyable() {
  return std::is_copy_constructible<T>() && std::is_copy_assignable<T>();
}

template <class T> constexpr bool Nostd::Semiregular() {
  return std::is_destructible<T>() && std::is_default_constructible<T>() &&
         Movable<T>() && Copyable<T>();
}

template <class T> constexpr bool Nostd::Regular() {
  return Semiregular<T>() && Equality_comparable<T>();
}

template <class T> constexpr bool Nostd::Streamable() {
  return Has_right_shift<T>() && Has_left_shift<T>();
}

#endif
