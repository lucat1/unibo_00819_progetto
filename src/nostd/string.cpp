/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Luca Tagliavini #971133
  03/09/2021

  string.cpp: implements the methods to construct, modify and do IO operations
  on a string of whide charters.
*/
#include "string.hpp"
#include <cstring>
#include <stdexcept>

Nostd::String::String(const String::allocator_type &alloc)
    : Vector(1, u'\0', alloc) {}

Nostd::String::String(const String &str, const String::allocator_type &alloc)
    : String(str.c_str(), alloc) {}

Nostd::String::String(const String &str, size_t start, size_t len,
                      const String::allocator_type &alloc)
    : Vector(len == npos ? str.size() - start : len + 1, alloc) {
  // we also check that we don't go out of the *str array as we
  // could loop infinitely when len = npos (read entire string)
  if (len == npos)
    len = str.length() - start;

  for (size_t i = 0; i < len; i++)
    v[i] = str[start + i];
  v[len] = u'\0';
}

Nostd::String::String(const char *str, const String::allocator_type &alloc)
    : String(str, strlen(str), alloc) {}

Nostd::String::String(const char *str, size_t len,
                      const String::allocator_type &alloc)
    : Vector(len + 1, alloc) {
  for (size_t i = 0; i < len; i++)
    v[i] = str[i];
  v[len] = u'\0';
}

Nostd::String::String(String &&str, const String::allocator_type &alloc)
    : Vector(str, alloc) {
  v = str.v;
  sz = str.sz;
  cap = str.cap;
  str.v = nullptr;
}

bool Nostd::String::empty() const {
  return sz <= 1 || (sz == 1 && v[0] == u'\0');
}

char *Nostd::String::c_str() const { return v; }
char *Nostd::String::data() const { return v; }
size_t Nostd::String::length() const { return sz - 1; }
size_t Nostd::String::max_size() const { return SIZE_MAX; }

// we override the Vector::resize to resize to a n+1 size and keep space for
// the '\0' char
void Nostd::String::resize(size_t n) {
  Vector::resize(n + 1);
  v[n] = u'\0';
}

// we override the Vector::clear to resize to size 1 and keep space for the
// '\0' char, using the previously defined method
void Nostd::String::clear() { resize(0); }

char &Nostd::String::back() { return v[sz - 2]; }
const char &Nostd::String::back() const { return v[sz - 2]; }

Nostd::String &Nostd::String::append(const Nostd::String &str) {
  return insert(sz - 1, str);
}

Nostd::String &Nostd::String::append(const char *str) {
  return insert(sz - 1, str);
}

void Nostd::String::push_back(const char c) {
  resize(sz); // increases the size by 1
  v[sz - 2] = c;
  v[sz - 1] = u'\0';
}

Nostd::String &Nostd::String::insert(size_t start, const Nostd::String &str,
                                     size_t substart, size_t subend) {
  String substr = str.substr(substart, subend);
  return insert(start, substr.c_str());
}

Nostd::String &Nostd::String::insert(size_t start, const char *str,
                                     size_t len) {
  // deliberately not using Vector::resize as we'd do the copying twice, which
  // is not smart at all. this method is therefore a modified copy of
  // Vector::resize
  if (len == npos)
    len = strlen(str);
  sz += len;
  calc_cap();
  char *newv = all_elems.allocate(cap);

  for (size_t i = 0; i < start; i++)
    newv[i] = v[i];

  for (size_t i = 0; i < len; i++)
    newv[start + i] = str[i];

  for (size_t i = start; i < sz - len; i++)
    newv[i + len] = v[i];

  all_elems.deallocate(v, cap);
  v = newv;
  return *this;
}

Nostd::String &Nostd::String::insert(size_t start, const char c) {
  char str[2] = {c, u'\0'};
  return insert(start, str);
}

int Nostd::String::compare(const Nostd::String &str) const {
  return compare(0, str.length(), str.c_str());
}
int Nostd::String::compare(size_t start, size_t len,
                           const Nostd::String &str) const {
  return compare(start, len, str.c_str());
}
int Nostd::String::compare(const char *str) const {
  return compare(0, strlen(str), str);
}
int Nostd::String::compare(size_t start, size_t len, const char *str,
                           size_t n) const {
  if (start > len)
    throw std::out_of_range("invalid start position in compare call");

  // n = npos means compare to the end of this->v
  if (n == npos)
    n = length() - start;
  return strncmp(v, str + start, n);
}
bool Nostd::String::operator==(const String &str) const {
  return !compare(str);
}
bool Nostd::String::operator!=(const String &str) const { return compare(str); }
size_t Nostd::String::find(Nostd::String &seq, size_t start) const {
  return find(seq.c_str(), start, seq.length());
}
size_t Nostd::String::find(const char *seq, size_t start) const {
  return find(seq, start, strlen(seq));
}
size_t Nostd::String::find(const char *seq, size_t start, size_t n) const {
  if (n == 0)
    return npos; // undefined behaviour, searching for an empty string

  for (size_t i = start; i < length(); i++)
    if (v[i] == seq[0] && strncmp(v + i, seq, n) == 0)
      return i;

  return npos;
}
size_t Nostd::String::find(const char c, size_t start) const {
  char str[2] = {c, u'\0'};
  return find(str, start);
}
Nostd::String Nostd::String::substr(size_t start, size_t len) const {
  String res(*this, start, len);
  return res;
}
Nostd::String Nostd::String::rtrim() {
  size_t i = length() - 1;
  while (i >= 0 && Nostd::iswspace(v[i]))
    i--;
  if (i == length() - 1)
    return *this;

  return substr(0, i);
}
Nostd::String Nostd::String::ltrim() {
  size_t i = 0;
  while (i < length() && Nostd::iswspace(v[i]))
    i++;
  if (i == 0)
    return *this;

  return substr(i);
}

Nostd::String &Nostd::String::operator=(const Nostd::String &str) {
  return operator=(str.c_str());
}

Nostd::String &Nostd::String::operator=(Nostd::String &&str) {
  all_elems.deallocate(v, cap);
  v = str.v;
  sz = str.sz;
  cap = str.cap;
  str.v = nullptr;
  return *this;
}

Nostd::String &Nostd::String::operator=(const char *str) {
  // we shrink/grow the vector deliberately by hand as we don't care
  // about the old string and therefore we can avoid the copy loop
  //
  // NOTE: we could reuse the previous vector if it's big enough but that
  // optimization will be put in place if we need to squeeze extra performance
  // from this
  all_elems.deallocate(v, cap);
  allocate_v(strlen(str) + 1);

  for (size_t i = 0; i < sz; i++) // = to copy the '\0' char
    v[i] = str[i];
  return *this;
}

Nostd::String &Nostd::String::operator=(const char c) {
  const char str[] = {c, u'\0'};
  return operator=(str);
}

Nostd::String &Nostd::String::operator+=(const Nostd::String &str) {
  append(str);
  return *this;
}

Nostd::String &Nostd::String::operator+=(const char *str) {
  append(str);
  return *this;
}

Nostd::String &Nostd::String::operator+=(const char c) {
  push_back(c);
  return *this;
}

// implemented the definition found at:
// https://en.cppreference.com/w/cpp/string/wide/iswspace
bool Nostd::iswspace(char c) {
  return c == u' ' || c == u'\f' || c == u'\n' || c == u'\r' || c == u'\t' ||
         c == u'\v';
}

std::basic_ostream<char> &Nostd::operator<<(std::ostream &os,
                                            const Nostd::String &str) {
  return os << str.c_str();
}

std::basic_istream<char> &Nostd::operator>>(std::istream &is,
                                            Nostd::String &str) {
  str.clear();
  char c;
  while (Nostd::iswspace(c = is.get()) && is.good())
    str.push_back(c);
  return is;
}

std::istream &Nostd::getline(std::istream &is, Nostd::String &str) {
  str.clear();
  char c;
  while ((c = is.get()) != u'\n' && is.good())
    str.push_back(c);
  return is;
}
