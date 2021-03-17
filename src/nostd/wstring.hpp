#ifndef WSTRING_HPP
#define WSTRING_HPP

#include "vector.hpp"
#include <wchar.h>

namespace Nostd {

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
    for (size_t i = start; i < len || str[i] == '\0'; i++)
      v[i - start] = str[i];
    if (len != npos) // make sure the last char is '\0' when we are not copying
                     // the string from start to the end
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

  WString &operator=(const wchar_t c) {
    resize(2);
    v[0] = c;
    v[1] = '\0';
    return *this;
  }

  WString &operator=(const wchar_t *str) {
    // we call it always as we could have some cases where shrinking
    // may be applied and therefore memory will be freed
    resize(wcslen(str) + 1);

    for (size_t i = 0; i <= wcslen(str); i++) // = to copy the '\0' char
      v[i] = str[i];
    return *this;
  }

  wchar_t *c_str() { return v; }
  size_t length() { return sz - 1; }
};

} // namespace Nostd

#endif // WSTRING_HPP
