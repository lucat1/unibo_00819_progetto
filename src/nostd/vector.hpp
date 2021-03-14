#ifndef NOSTD_VECTOR_HPP
#define NOSTD_VECTOR_HPP
#include <stddef.h>

namespace Nostd {
class Vector {
 private:
  int* v;
  size_t sz, cap;

 public:
  Vector();
  explicit Vector(size_t size);
  void push_back(int ele);
  void clear();
  int& at(size_t);
  size_t erase(size_t);
  void resize(size_t);
  size_t size();
  size_t capacity();
};
}  // namespace Nostd

#endif