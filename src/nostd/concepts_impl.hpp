/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Stefano Volpe #969766
  03/19/2021

  concepts_impl.hpp: implementer interface of generic programming concepts
  (which will be introduced as an actual language facility only in C++20)
*/

#ifndef NOSTD_CONCEPTS_IMPL_HPP
#define NOSTD_ALLOCATOR_IMPL_HPP

#include "concepts.hpp"

#include <type_traits>

namespace Nostd {

/*
  "Has_f" type predicates as generic programming constraints.
  See B. Stroustrup, The C++ Programming Language, 4th ed., Pearson 2013, p.
  799f.
*/
struct SubstitutionFailure {};

template <class T> struct SubstitutionSucceeded : std::true_type {};

template <>
struct SubstitutionSucceeded<SubstitutionFailure> : std::false_type {};

template <class T> struct Equal_result {
private:
  template <class X>
  static auto check(X const &x, X const &y) -> decltype(x == y);
  static SubstitutionFailure check(...);

public:
  using type = decltype(check(std::declval<T>()));
};

template <class T>
struct Has_equal_trait : SubstitutionSucceeded<class Equal_result<T>::type> {};

template <class T> constexpr bool Has_equal();

template <class T> struct Not_equal_result {
private:
  template <class X>
  static auto check(X const &x, X const &y) -> decltype(x == y);
  static SubstitutionFailure check(...);

public:
  using type = decltype(check(std::declval<T>()));
};

template <class T>
struct Has_not_equal_trait
    : SubstitutionSucceeded<class Equal_result<T>::type> {};

template <class T> constexpr bool Has_not_equal();

template <class T> struct Right_shift_result {
private:
  template <class X>
  static auto check(X const &x, X const &y) -> decltype(x >> y);
  static SubstitutionFailure check(...);

public:
  using type = decltype(check(std::declval<T>()));
};

template <class T>
struct Has_right_shift_trait
    : SubstitutionSucceeded<class Right_shift_result<T>::type> {};

template <class T> constexpr bool Has_right_shift();

template <class T> struct Left_shift_result {
private:
  template <class X>
  static auto check(X const &x, X const &y) -> decltype(x >> y);
  static SubstitutionFailure check(...);

public:
  using type = decltype(check(std::declval<T>()));
};

template <class T>
struct Has_left_shift_trait
    : SubstitutionSucceeded<class Left_shift_result<T>::type> {};

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
