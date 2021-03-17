/*
  University of Bologna
  First cicly degree in Computer Science
  00819 - Programmazione

  Stefano Volpe #969766
  03/17/2021

  allocator.hpp: user interface of Nostd::Allocator and its helper functions.
*/

#ifndef NOSTD_ALLOCATOR_HPP
#define NOSTD_ALLOCATOR_HPP

#include <cstddef>

namespace Nostd {
template <class T> class Allocator;
template <> class Allocator<void>;

/*
  You can refer to Allocator<void> as long as you do not dereference its
  pointers. For this specialization, std::Allocator uses "typedef" notation
  instead.
*/
template <> class Allocator<void> {
public:
  using pointer = void *;
  using const_pointer = const void *;
  using value_type = void;
  // std::Allocator uses a struct instead (arcaism)
  template <class U> using other = Allocator<U>;
};

/*
  A class defining the default memory model to be used. It manages memory
  allocations using "new" and deallocations using "delete".
*/
template <class T> class Allocator {
public:
  using value_type = T;
  using pointer = T *;
  using reference = T &;
  using const_pointer = const T *;
  using const_reference = const T &;
  using size_type = size_t;
  using difference_type = ptrdiff_t;
  // std::Allocator uses a struct instead (arcaism)
  template <class U> using other = Allocator<U>;

  Allocator() noexcept;
  Allocator(const Allocator &) noexcept;
  template <class U> Allocator(const Allocator<U> &) noexcept;
  ~Allocator() noexcept;

  pointer address(reference) const noexcept;
  const_pointer address(const_reference) const noexcept;
  // std::Allocator uses 0 ad default hint instead
  pointer allocate(size_type, Allocator<void>::const_pointer hint = nullptr);
  void deallocate(pointer, size_type);
  size_type max_size() const noexcept;
  template <class U, class... Args> void construct(U *p, Args &&...args);
  template <class U> void destroy(U *p);
};

} // namespace Nostd

#endif
