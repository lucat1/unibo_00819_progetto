/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Stefano Volpe #969766
  04/03/2021

  database.cpp: implementation of Data::Database and its helper entities.
*/

#include "database.hpp"

using namespace Data;
using Nostd::Vector;
const auto &separator = Database::separator;
const auto &newrecord = Database::newrecord;
const auto &escape = Database::escape;

constexpr wchar_t Database::separator, Database::newrecord, Database::escape;

Database::Database(const char *filename) {
  // TODO
}

Vector<Result> &Database::results() noexcept { return res; }

const Vector<Result> &Database::results() const noexcept { return res; }

void Database::save_results() const {
  // TODO
}

Vector<Setting> &Database::settings() noexcept { return set; }

const Vector<Setting> &Database::settings() const noexcept { return set; }

void Database::save_settings() const {
  // TODO
}

Vector<Map> &Database::maps() noexcept { return map; }

const Vector<Map> &Database::maps() const noexcept { return map; }

Vector<Scenery> &Database::sceneries() noexcept { return sce; }

const Vector<Scenery> &Database::sceneries() const noexcept { return sce; }

std::basic_istream<wchar_t> &
Data::get_CSV_WString(std::basic_istream<wchar_t> &is, Nostd::WString &s) {
  s.clear();
  wchar_t input;
  while ((input = is.get()) != separator && input != newrecord) {
    s.push_back(is.get());
    if (s.back() == escape)
      is.get(s.back());
  }
  return is;
}

std::basic_ostream<wchar_t> &
Data::put_CSV_WString(std::basic_ostream<wchar_t> &os,
                      const Nostd::WString &s) {
  for (auto x : s) {
    if (x == separator || x == newrecord)
      os << escape;
    os << escape;
  }
  return os;
}
