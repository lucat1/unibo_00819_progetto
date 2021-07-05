/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Luca Tagliavini #971133
  03/09/2021

  string.hpp: defines the public interface for a string of wide charters. It is
  resizeable and provides various helpers for common actions on strings such as
  split, find, concatenation, etc.
*/
#ifndef NOSTD_STRING_HPP
#define NOSTD_STRING_HPP

#include "vector.hpp"
#include <cwchar>
#include <istream>
#include <ostream>

namespace Nostd {

// String implements a growable array of `char` chars that make up a string.
// Differences from std::string:
// - size() returns length() + 1 (as it's the size of the underlying vector)
// +1 is for the '\0' null char
// - gone are also all assing(*) methods which match the ones available as
// consturctors. We currently don't have a use-case for those
// - the copy(*) method has been left out as we currently have no use for it
// and furthermore can be easily matched by the copy constructor/operator
// - comparisons of _two_ substrings are left out for simplicity, but can be
// added fairly easily if deemed necessary
class String : public Vector<char> {
  using Vector::allocator_type;

public:
  // index used to mean two concepts:
  // - run an operation to the end of the string (be it a copy, substring, etc)
  // - no references of the searched substring were found (relative to the found
  // method)
  static const size_t npos = -1;

  // constructs an empty String
  explicit String(const allocator_type &alloc = allocator_type());
  // construct a String from another String copying its content
  String(const String &str, const allocator_type &alloc = allocator_type());
  // construct a String from another String from start to start+len
  String(const String &str, size_t start, size_t len = npos,
          const allocator_type &alloc = allocator_type());
  // constructs a String from a c-style string
  String(const char *str, const allocator_type &alloc = allocator_type());
  // constructs a String from a c-style string limiting its length
  String(const char *str, size_t len,
          const allocator_type &alloc = allocator_type());
  // construct a String from another _temporary_ String copying its content
  String(String &&str, const allocator_type &alloc = allocator_type());

  // checks whether the String is empty
  bool empty() const;
  // returns the underlying char vector
  char *c_str() const;
  // returns the underlying char vector
  char *data() const;
  // returns the length of the stored string
  size_t length() const;
  // returns the maximum length of a string imposed by hardware limitatinos
  size_t max_size() const;

  // resizes the string and trims any exrta chars
  void resize(size_t n);
  // clears the string content
  void clear();
  // returns a reference to the last character of the string
  char &back();
  const char &back() const;
  // appends another String at the end of this instance (copying its contents)
  String &append(const String &str);
  // appends a copy of a char* at the end of this instance
  String &append(const char *str);
  // postpends a charter to the string
  void push_back(const char c);
  // inserts a String in between the current string instance, copying it
  String &insert(size_t start, const String &str, size_t substart = 0,
                  size_t subend = npos);
  // inserts the chars of a char* in between the current string
  String &insert(size_t start, const char *str, size_t len = npos);
  // inserts the a char at the given position in the string
  String &insert(size_t start, const char c);

  // compares the two Strings
  int compare(const String &str) const;
  // compares the two Strings with an offset and only up to a given length
  int compare(size_t start, size_t len, const String &str) const;
  // compares this instance with a given string
  int compare(const char *str) const;
  // compares this instance with a given string, starting from a start index and
  // only computing n checks
  int compare(size_t start, size_t len, const char *str,
              size_t n = npos) const;
  // compare the two Strings
  bool operator==(const String &str) const;
  bool operator!=(const String &str) const;
  // looks for the given String sequence starting from the given index and
  // returns the position of the subsequence if found, npos otherwhise
  size_t find(String &seq, size_t start = 0) const;
  // looks for the given char* sequence starting from the given index and
  // returns the position of the subsequence if found, npos otherwhise
  size_t find(const char *seq, size_t start = 0) const;
  // looks for the given char* sequence starting from the given index and
  // returns the position of the subsequence if found, npos otherwhise. It also
  // makes sure to only check n chars from the starting position.
  size_t find(const char *seq, size_t start, size_t n) const;
  // looks for the given char char starting from the given index and returns
  // the position of the first occourence if any, npos otherwhise.
  size_t find(const char c, size_t start = 0) const;
  // returns a String instance where the chars from start to start+len have
  // been copied over
  String substr(size_t start = 0, size_t len = npos) const;
  // trims whitespace from the right
  String rtrim();
  // trims whitespace from the left
  String ltrim();

  // various operators

  String &operator=(const String &str);
  String &operator=(String &&str);
  String &operator=(const char *str);
  String &operator=(const char c);
  String &operator+=(const String &str);
  String &operator+=(const char *str);
  String &operator+=(const char c);
};

bool iswspace(char c);

std::basic_ostream<char> &operator<<(std::ostream &os,
                                        const String &str);
std::basic_istream<char> &operator>>(std::istream &os,
                                        String &str);
std::basic_istream<char> &getline(std::istream &os,
                                     String &str);

} // namespace Nostd

#endif // NOSTD_STRING_HPP
