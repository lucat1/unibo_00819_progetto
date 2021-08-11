/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Stefano Volpe #969766
  03/18/2021

  concepts.hpp: generic programming concepts (which will be introduced as an
  actual language facility only in C++20)
*/

#ifndef NOSTD_CONCEPTS_HPP
#define NOSTD_CONCEPTS_HPP

#include <type_traits>

#include "concepts_impl.hpp"

namespace Nostd {

/*
  Checks whether type T has == operator.
*/
template <class T> constexpr bool Has_equal();

/*
  Checks whether type T has != operator.
*/
template <class T> constexpr bool Has_not_equal();

/*
  Checks whether type T has >> operator.
*/
template <class T> constexpr bool Has_right_shift();

/*
  Checks whether type T has << operator.
*/
template <class T> constexpr bool Has_left_shift();

/*
  Checks whether type T is boolean.
*/
template <class T> constexpr bool Boolean();

/*
  Checks whether type T has both == and != operators, and whether they both
  return a boolean.
*/
template <class T> constexpr bool Equality_comparable();

/*
  Checks whether type T has a move constructor and a move assignment operator.
*/
template <class T> constexpr bool Movable();

/*
  Checks whether type T has a copy constructor and a copy assignment operator.
*/
template <class T> constexpr bool Copyable();

/*
  A type is said to be "semiregular" when it is both default constructible and
  copyable.
*/
template <class T> constexpr bool Semiregular();

/*
  A type is said to be "regular" when it is both semiregular and equality
  comparable.
*/
template <class T> constexpr bool Regular();

/*
  A type is said to be "streamable" when it is both input and output
  streamable.
*/
template <class T> constexpr bool Streamable();

} // namespace Nostd

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
  return Has_equal<T>() && Boolean<typename Equal_result<T>::type>() &&
         Has_not_equal<T>() && Boolean<typename Not_equal_result<T>::type>();
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
