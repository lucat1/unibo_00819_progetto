#ifndef WSTRING_HPP
#define WSTRING_HPP

#include <vector>
#include <wchar.h>

namespace Nostd {

class WString : public std::vector<wchar_t> {
public:
  WString() : std::vector(1, '') {}
  explicit WString(const size_t len) : Vector(len) {
    // explicitly set the first char to '\0' because we want to make sure tat
    // a possible wcslen (aka strlen) call on the vector goes into an infinite
    // loop not finding the '\0' terminator char in the memory allocated to the
    // string, which we do not initialize to improve performance
    //
    // a more conservative approach could be taken so that we initialize the
    // entire length of the string to null chars. This is oftentimes the case in
    // the C standard library
    v[0] = '\0';
  }
  explicit WString(const wchar_t *str) : Vector(wcslen(str)) {
    for (size_t i = 0; i < wcslen(str); i++)
      v[i] = str[i];
  }
};

} // namespace Nostd

#endif // WSTRING_HPP
