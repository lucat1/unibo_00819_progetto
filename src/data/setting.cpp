/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Stefano Volpe #969766
  04/02/2021

  setting.cpp: implementation of Data::Setting and its helper entities.
*/

#include "setting.hpp"

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
  if (-n > pos)
    throw std::out_of_range("-n > pos");
  return Iterator(s, pos + n);
}

Iterator Iterator::operator-(difference_type n) const {
  return Iterator(s, pos - n);
}

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
