/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Stefano Volpe #969766
  04/02/2021

  setting.cpp: implementation of Data::Setting and its helper entities.
*/

#include "setting.hpp"

#include <iterator>
#include <stdexcept>

using Data::Setting;
using Iterator = Setting::Iterator;

Iterator::Iterator(const Setting *setting, size_t position) : s{setting} {
  if (position > s->size())
    throw std::out_of_range("position > s->size()");
  pos = position;
}

Iterator &Iterator::operator++() { return *this += 1; }

Iterator Iterator::operator++(int) {
  Iterator res{*this};
  ++*this;
  return res;
}

Iterator &Iterator::operator--() { return *this -= 1; }

Iterator Iterator::operator--(int) {
  Iterator res{*this};
  --*this;
  return res;
}

Iterator Iterator::operator+(difference_type n) const {
  if (static_cast<difference_type>(pos) + n < 0)
    throw std::out_of_range("static_cast<difference_type>(pos) + n < 0");
  return Iterator(s, static_cast<difference_type>(pos) + n);
}

Iterator Iterator::operator-(difference_type n) const { return *this + -n; }

Setting::difference_type Iterator::operator-(Iterator i) const {
  if (s != i.s)
    throw std::domain_error("iterators from different settings");
  return static_cast<difference_type>(pos) - i.pos;
}

Iterator &Iterator::operator+=(difference_type n) { return *this = *this + n; }

Iterator &Iterator::operator-=(difference_type n) { return *this = *this - n; }

bool Iterator::operator==(const Iterator &i) const noexcept {
  return s == i.s && pos == i.pos;
}

bool Iterator::operator!=(const Iterator &i) const noexcept {
  return !(*this == i);
}

bool Iterator::operator<(const Iterator &i) const {
  if (s != i.s)
    throw std::domain_error("iterators from different settings");
  return pos < i.pos;
}

bool Iterator::operator>(const Iterator &i) const { return !(*this <= i); }

bool Iterator::operator<=(const Iterator &i) const {
  return *this < i || *this == i;
}

bool Iterator::operator>=(const Iterator &i) const { return !(*this < i); }

int Iterator::operator*() const { return (*s)[pos]; }

int Iterator::operator[](size_t n) const { return *(*this + n); }

Setting::Setting(const Nostd::WString &label, int start, size_t size,
                 int stride, size_t default_index)
    : Setting(label, start, size, stride, default_index, default_index){};

Setting::Setting(const Nostd::WString &label, int start, size_t size,
                 int stride, size_t default_index, size_t current_index)
    : lbl{label}, strt{start}, strd{stride}, sz{size}, def_ind{default_index},
      curr_ind{current_index} {
  if (!sz)
    throw std::invalid_argument("!sz");
  if (!strd)
    throw std::invalid_argument("!strd");
  if (def_ind >= sz)
    throw std::out_of_range("def_ind >= sz");
  if (curr_ind >= sz)
    throw std::out_of_range("curr_ind >= sz");
}

auto Setting::begin() const noexcept -> iterator { return Iterator(this, 0); }

auto Setting::end() const noexcept -> iterator { return Iterator(this, sz); }

auto Setting::rbegin() const noexcept -> reverse_iterator {
  return std::reverse_iterator<iterator>(end() - 1);
}

auto Setting::rend() const noexcept -> reverse_iterator {
  return std::reverse_iterator<iterator>(begin()) + 1;
}

auto Setting::default_value() const noexcept -> iterator {
  return begin() + def_ind;
}

auto Setting::rdefault_value() const noexcept -> reverse_iterator {
  return std::reverse_iterator<iterator>(default_value());
}

auto Setting::current_value() const noexcept -> iterator {
  return begin() + curr_ind;
}

auto Setting::rcurrent_value() const noexcept -> reverse_iterator {
  return std::reverse_iterator<iterator>(current_value());
}

int Setting::set(const iterator &i) {
  if (i == end())
    throw std::invalid_argument("i == end()");
  return at(curr_ind = i - begin());
}

int Setting::rset(const reverse_iterator &i) {
  if (i == rend())
    throw std::invalid_argument("i == rend()");
  return at(curr_ind = i - rbegin());
}

const Nostd::WString &Setting::label() const noexcept { return lbl; }

auto Setting::size() const noexcept -> size_type { return sz; }

int Setting::stride() const noexcept { return strd; }

int Setting::operator[](size_type n) const noexcept { return strt + n * strd; }

int Setting::at(size_type n) const {
  if (n >= sz)
    throw std::out_of_range("n >= sz");
  return (*this)[n];
}

std::basic_istream<wchar_t> &Data::operator>>(std::basic_istream<wchar_t> &is,
                                              Setting &s) {
  Nostd::WString label;
  int start, stride;
  size_t size, default_index, current_index;
  Nostd::getline(is, label) >> start >> size >> stride >> default_index >>
      current_index;
  s = Setting(label, start, size, stride, default_index, current_index);
  return is;
}

std::basic_ostream<wchar_t> &Data::operator<<(std::basic_ostream<wchar_t> &os,
                                              const Setting &s) {
  return os << s.label() << s.strt << s.sz << s.def_ind << s.curr_ind;
}
