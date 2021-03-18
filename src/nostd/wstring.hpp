#ifndef WSTRING_HPP
#define WSTRING_HPP

#include "vector.hpp"
#include <stdexcept>
#include <wchar.h>

namespace Nostd {

// WString implements a growable array of wchar_t chars that make up a string.
// Differences from std::wstring:
// - size() returns length() + 1 (as it's the size of the underlying vector)
// +1 is for the '\0' null char
// - rimossi i meotdi assign(*) che combaciano con i costruttori. In caso di
// necessita' possono essere implementati
class WString : public Vector<wchar_t> {
public:
  // when used for substrings meants "'til the end"
  static const size_t npos = -1;

  // constructs an empty WString
  explicit WString() : Vector(1, '\0') {}

  // construct a WString from another WString copying its content
  WString(WString &str) : Vector(str.size()) {
    for (size_t i = 0; i < str.size(); i++)
      v[i] = str[i];
  }

  // construct a WString from another WString from start to start+len
  WString(WString &str, size_t start, size_t len = npos)
      : Vector(len == npos ? str.size() - start : len - start + 1) {
    // we also check that we don't go out of the *str array as we
    // could loop infinitely when len = npos (read entire string)
    if (len == npos)
      len = str.length();

    for (size_t i = start; i < len || str[i] != '\0'; i++)
      v[i - start] = str[i];
    v[len - start] = '\0';
  }

  // constructs a WString from a c-style string
  WString(const wchar_t *str) : Vector(wcslen(str) + 1) {
    for (size_t i = 0; str[i] != '\0'; i++)
      v[i] = str[i];
  }

  // constructs a WString from a c-style string limiting its length
  WString(const wchar_t *str, size_t len) : Vector(len + 1) {
    for (size_t i = 0; i < len + 1; i++)
      v[i] = str[i];
    v[len] = '\0';
  }

  // construct a WString from another _temporary_ WString copying its content
  WString(WString &&str) : Vector(str.size()) {
    delete[] v;
    v = str.v;
    sz = str.sz;
    cap = str.cap;
    str.v = nullptr;
  }

  // checks whether the WString is empty
  bool empty() { return sz <= 1 || (sz == 1 && v[0] == '\0'); }

  wchar_t *c_str() { return v; }
  size_t length() { return sz - 1; }
  size_t max_size() { return SIZE_MAX; }

  // we override the Vector::resize to resize to a n+1 size and keep space for
  // the '\0' char
  void resize(size_t n) {
    Vector::resize(n + 1);
    v[n] = '\0';
  }

  // we override the Vector::celar to resize to size 1 and keep space for the
  // '\0' char
  void clear() {
    Vector::resize(1);
    v[0] = '\0';
  }

  wchar_t &back() {
    if (empty())
      throw std::invalid_argument("called WString::back on an empty string");
    return v[0];
  }

  wchar_t &front() {
    if (empty())
      throw std::invalid_argument("called WString::front on an empty string");
    return v[sz - 2];
  }

  // appends another WString at the end of this instance (copying its contents)
  WString &append(WString &str) { return insert(sz - 1, str); }

  WString &append(const wchar_t *str) { return insert(sz - 1, str); }

  void push_back(const wchar_t c) {
    resize(sz); // increases the size by 1
    v[sz - 2] = c;
    v[sz - 1] = '\0';
  }

  WString &insert(size_t start, WString &str, size_t substart = 0,
                  size_t subend = npos) {
    WString substr = str.substr(substart, subend);
    return insert(start, substr.c_str());
  }

  WString &insert(size_t start, const wchar_t *str, size_t len = npos) {
    // deliberately not using Vector::resize as we'd do the copying twice, which
    // is not smart at all. this method is therefore a modified copy of
    // Vector::resize
    if (len == npos)
      len = wcslen(str);
    sz += len;
    calc_cap();
    wchar_t *newv = new wchar_t[cap];

    for (size_t i = 0; i < start; i++)
      newv[i] = v[i];

    for (size_t i = 0; i < len; i++)
      newv[start + i] = str[i];

    for (size_t i = start; i < sz - len - 1; i++)
      newv[i + len] = v[i];

    delete[] v;
    v = newv;
    return *this;
  }

  WString &insert(size_t start, const wchar_t c) {
    wchar_t str[2] = {c, '\0'};
    return insert(start, str);
  }

  WString substr(size_t start = 0, size_t len = npos) {
    WString res(*this, start, len);
    return res;
  }
  // TODO: operations

  WString &operator=(WString &str) {
    Vector::resize(str.size());

    for (size_t i = 0; i < str.size(); i++) // = to copy the '\0' char
      v[i] = str[i];
    return *this;
  }

  WString &operator=(const wchar_t *str) {
    // we call it always as we could have some cases where shrinking
    // may be applied and therefore memory will be freed
    Vector::resize(wcslen(str) + 1);

    for (size_t i = 0; i <= wcslen(str); i++) // = to copy the '\0' char
      v[i] = str[i];
    return *this;
  }
  WString &operator=(const wchar_t c) {
    Vector::resize(2);
    v[0] = c;
    v[1] = '\0';
    return *this;
  }

  WString &operator+=(WString &str) {
    append(str);
    return *this;
  }
  WString &operator+=(const wchar_t *str) {
    append(str);
    return *this;
  }
  WString &operator+=(const wchar_t c) {
    push_back(c);
    return *this;
  }
};

} // namespace Nostd

#endif // WSTRING_HPP
