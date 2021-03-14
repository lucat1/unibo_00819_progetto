#include "vector.hpp"
#include <stdexcept>

Nostd::Vector::Vector() {
  Vector(0);
}

Nostd::Vector::Vector(size_t size) {
  sz = size;
  if (size == 0)
    cap = 1;
  else
    cap = size * 1.5;
  v = new int[cap];
}
void Nostd::Vector::push_back(int ele) {
  if (sz == cap)
    resize(sz);
  v[sz++] = ele;
}

void Nostd::Vector::clear() {
  resize(0);
}
void Nostd::Vector::resize(size_t n) {
  sz = n;
  if (n == 0)
    cap = 1;
  else
    cap = n * 1.5;
  int* newv = new int[cap];
  for (size_t i = 0; i < n; i++)
    newv[i] = v[i];
  delete v;
  v = newv;
}

int& Nostd::Vector::at(size_t i) {
  if (i >= sz)
    throw std::invalid_argument("index out of bounds");
  return v[i];
}

size_t Nostd::Vector::erase(size_t i) {
  if (i >= sz)
    throw std::invalid_argument("index out of bounds");

  for (size_t k = i; k < sz - 1; k++)
    v[k] = v[k + 1];

  if (sz >= cap * 2 / 3)
    sz = sz - 1;
  else
    resize(sz - 1);

  return i;
}

size_t Nostd::Vector::size() {
  return sz;
}

size_t Nostd::Vector::capacity() {
  return cap;
}