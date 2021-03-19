/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Stefano Volpe #969766
  03/18/2021

  concepts.hpp: user interface of generic programming concepts (which will be
  introduced as an actual language facility only in C++20)
*/

#ifndef NOSTD_CONCEPTS_HPP
#define NOSTD_CONCEPTS_HPP

namespace Nostd {

template <class T> constexpr bool Has_equal();

template <class T> constexpr bool Has_not_equal();

template <class T> constexpr bool Has_right_shift();

template <class T> constexpr bool Has_left_shift();

template <class T> constexpr bool Boolean();

template <class T> constexpr bool Equality_comparable();

template <class T> constexpr bool Movable();

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

#endif
