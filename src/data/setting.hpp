/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Stefano Volpe #969766
  04/01/2021

  setting.hpp: user interface of Data::Setting and its helper entities.
*/

#ifndef DATA_SETTING_HPP
#define DATA_SETTING_HPP

#include <iostream>
#include <iterator>

#include "../nostd/wstring.hpp"

namespace Data {

/*
  A class representing a game setting. It defines both the aspects defined by
  the game designer (label, possible values, and default value) and its current
  state (which can be set by the player).
*/
class Setting {
public:
  class Iterator;

  using iterator = Iterator;
  using size_type = size_t;
  using difference_type = ptrdiff_t;

  /*
    A random access iterator pointing to a (virtual) element among the values
    a Setting can assume.
  */
  class Iterator : public std::iterator<std::random_access_iterator_tag, int> {
  public:
    Iterator() = default;
    Iterator(const Setting *, size_t position = 0);
    Iterator(Iterator &&) = default;
    Iterator &operator=(Iterator &&) = default;
    Iterator(const Iterator &) = default;
    Iterator &operator=(const Iterator &) = default;
    ~Iterator() = default;

    Iterator &operator++();
    Iterator operator++(int);
    Iterator &operator--();
    Iterator operator--(int);
    Iterator operator+(difference_type) const;
    Iterator operator-(difference_type) const;
    difference_type operator-(Iterator) const;
    Iterator &operator+=(difference_type);
    Iterator &operator-=(difference_type);

    bool operator==(const Iterator &) const noexcept;
    bool operator!=(const Iterator &) const noexcept;
    bool operator<(const Iterator &) const;
    bool operator>(const Iterator &) const;
    bool operator<=(const Iterator &) const;
    bool operator>=(const Iterator &) const;

    // as the values themselves are virtual, dereferencing an iterator actually
    // returns a value, instead of an rvalue reference. Also, -> is obviously
    // unsupported.
    int operator*() const;
    int operator[](size_t) const;

  private:
    const Setting *s{nullptr};
    size_t pos{0};
  };

  Setting() = delete;
  // label: name of the Setting
  // start: lowest possible value
  // size: number of possible values (cannot be 0)
  // stride: step between possible values (cannot be 0)
  // default_index: index (starting from 0) of default value
  Setting(Nostd::WString label, int start = 0, size_t size = 2, int stride = 1,
          size_t default_index = 0);
  // current_index: index (starting from 0) of default value. If not specified,
  // it is the same as default_index
  Setting(Nostd::WString label, int start, size_t size, int stride,
          size_t default_index, size_t current_index);

  // move
  Setting(Setting &&) = default;
  Setting &operator=(Setting &&) = default;

  // copy
  Setting(const Setting &) = default;
  Setting &operator=(const Setting &) = default;

  ~Setting() = default;

  // iteratros
  iterator begin() const noexcept;
  iterator end() const noexcept;
  iterator default_value() const noexcept;
  iterator current_value() const noexcept;
  // the following two methods update the current value
  int set(const iterator &);

  // getters
  const Nostd::WString &label() const noexcept;
  size_type size() const noexcept;
  int stride() const noexcept;
  int first() const noexcept;
  int last() const noexcept;

  // element access
  int operator[](size_type) const noexcept;
  int at(size_type) const;

  friend std::basic_ostream<wchar_t> &operator<<(std::basic_ostream<wchar_t> &,
                                                 const Setting &);

private:
  Nostd::WString lbl;
  int strt, strd;
  size_t sz, def_ind, curr_ind;
};

// The two following methods ignore the setting's current value and work with
// non-standard CSV format
std::basic_istream<wchar_t> &operator>>(std::basic_istream<wchar_t> &,
                                        Setting &);
std::basic_ostream<wchar_t> &operator<<(std::basic_ostream<wchar_t> &,
                                        const Setting &);

} // namespace Data

#endif