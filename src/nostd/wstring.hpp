/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Luca Tagliavini #971133
  03/09/2021

  wstring.hpp: defines the public interface for a string of wide charters. It is
  resizeable and provides various helpers for common actions on strings such as
  split, find, concatenation, etc.
*/
#ifndef NOSTD_WSTRING_HPP
#define NOSTD_WSTRING_HPP

#include "vector.hpp"
#include <cwchar>
#include <istream>
#include <ostream>

namespace Nostd {

// WString implements a growable array of wchar_t chars that make up a string.
// Differences from std::wstring:
// - size() returns length() + 1 (as it's the size of the underlying vector)
// +1 is for the '\0' null char
// - gone are also all assing(*) methods which match the ones available as
// consturctors. We currently don't have a use-case for those
// - the copy(*) method has been left out as we currently have no use for it
// and furthermore can be easily matched by wcscpy(dest, wstring::c_str)
// - comparisons of _two_ substrings are left out for simplicity, but can be
// added fairly easily if deemed necessary
class WString : public Vector<wchar_t> {
  using Vector::allocator_type;

public:
  // index used to mean two concepts:
  // - run an operation to the end of the string (be it a copy, substring, etc)
  // - no references of the searched substring were found (relative to the found
  // method)
  static const size_t npos = -1;

  // constructs an empty WString
  explicit WString(const allocator_type &alloc = allocator_type());
  // construct a WString from another WString copying its content
  WString(const WString &str, const allocator_type &alloc = allocator_type());
  // construct a WString from another WString from start to start+len
  WString(const WString &str, size_t start, size_t len = npos,
          const allocator_type &alloc = allocator_type());
  // constructs a WString from a c-style string
  WString(const wchar_t *str, const allocator_type &alloc = allocator_type());
  // constructs a WString from a c-style string limiting its length
  WString(const wchar_t *str, size_t len,
          const allocator_type &alloc = allocator_type());
  // construct a WString from another _temporary_ WString copying its content
  WString(WString &&str, const allocator_type &alloc = allocator_type());

  // checks whether the WString is empty
  bool empty() const;
  // returns the underlying wchar_t vector
  wchar_t *c_str() const;
  // returns the underlying wchar_t vector
  wchar_t *data() const;
  // returns the length of the stored string
  size_t length() const;
  // returns the maximum length of a string imposed by hardware limitatinos
  size_t max_size() const;

  // resizes the string and trims any exrta chars
  void resize(size_t n);
  // clears the string content
  void clear();
  // returns the frist char in the string
  wchar_t &front();
  // returns the last char in the string
  wchar_t &back();
  // appends another WString at the end of this instance (copying its contents)
  WString &append(const WString &str);
  // appends a copy of a wchar_t* at the end of this instance
  WString &append(const wchar_t *str);
  // postpends a charter to the string
  void push_back(const wchar_t c);
  // inserts a WString in between the current string instance, copying it
  WString &insert(size_t start, const WString &str, size_t substart = 0,
                  size_t subend = npos);
  // inserts the chars of a wchar_t* in between the current string
  WString &insert(size_t start, const wchar_t *str, size_t len = npos);
  // inserts the a wchar_t at the given position in the string
  WString &insert(size_t start, const wchar_t c);

  // compares the two WStrings
  int compare(WString &str) const;
  // compares the two WStrings with an offset and only up to a given length
  int compare(size_t start, size_t len, WString &str) const;
  // compares this instance with a given string
  int compare(const wchar_t *str) const;
  // compares this instance with a given string, starting from a start index and
  // only computing n checks
  int compare(size_t start, size_t len, const wchar_t *str,
              size_t n = npos) const;
  // looks for the given WString sequence starting from the given index and
  // returns the position of the subsequence if found, npos otherwhise
  size_t find(WString &seq, size_t start = 0) const;
  // looks for the given wchar_t* sequence starting from the given index and
  // returns the position of the subsequence if found, npos otherwhise
  size_t find(const wchar_t *seq, size_t start = 0) const;
  // looks for the given wchar_t* sequence starting from the given index and
  // returns the position of the subsequence if found, npos otherwhise. It also
  // makes sure to only check n chars from the starting position.
  size_t find(const wchar_t *seq, size_t start, size_t n) const;
  // looks for the given wchar_t char starting from the given index and returns
  // the position of the first occourence if any, npos otherwhise.
  size_t find(const wchar_t c, size_t start = 0) const;
  // returns a WString instance where the chars from start to start+len have
  // been copied over
  WString substr(size_t start = 0, size_t len = npos) const;
  // trims whitespace from the right
  WString rtrim();
  // trims whitespace from the left
  WString ltrim();

  // various operators

  WString &operator=(const WString &str);
  WString &operator=(WString &&str);
  WString &operator=(const wchar_t *str);
  WString &operator=(const wchar_t c);
  WString &operator+=(const WString &str);
  WString &operator+=(const wchar_t *str);
  WString &operator+=(const wchar_t c);
};

bool iswspace(wchar_t c);

std::basic_ostream<wchar_t> &operator<<(std::basic_ostream<wchar_t> &os,
                                        const WString &str);
std::basic_istream<wchar_t> &operator>>(std::basic_istream<wchar_t> &os,
                                        WString &str);
std::basic_istream<wchar_t> &getline(std::basic_istream<wchar_t> &os,
                                     WString &str);

} // namespace Nostd

#endif // NOSTD_WSTRING_HPP
