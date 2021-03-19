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

/*
  A type is said to be "semiregular" when it is both default constructible and
  copyable.
*/
template <class T> constexpr bool Nostd::Semiregular() {
  return std::is_destructible<T>() && std::is_default_constructible<T>() &&
         Movable<T>() && Copyable<T>();
}

/*
  A type is said to be "regular" when it is both semiregular and equality
  comparable.
*/
template <class T> constexpr bool Nostd::Regular() {
  return Semiregular<T>() && Equality_comparable<T>();
}

#endif
