/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Stefano Volpe #969766
  04/03/2021

  database.cpp: implementation of Data::Database and its helper entities.
*/

#include "database.hpp"

#include <cstring>
#include <fstream>

using namespace Data;
using Nostd::UnorderedMap;
using Nostd::Vector;
using Nostd::WString;

constexpr wchar_t Database::separator, Database::newrecord, Database::escape;

Database::Database(const char *configuration, const char *assets,
                   const char *scoreboard)
    : conf{newstrcpy(configuration)}, scor{newstrcpy(scoreboard)} {
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

char *Database::newstrcpy(const char *str) const {
  return std::strcpy(new char[std::strlen(str) + 1], str);
}

char *Database::newstrcat(const char *str1, const char *str2) const {
  return std::strcat(
      std::strcpy(new char[std::strlen(str1) + std::strlen(str2) + 1], str1),
      str2);
}

void Database::load_settings(const char *assets_filepath) {
  // game settings
  const char *const settings_fp{newstrcat(assets_filepath, settings_rel_fp)};
  std::wifstream wifs{settings_fp};
  Setting s;
  while (wifs >> s)
    set.push_back(s);
  wifs.close();
  // current values
  wifs.open(conf);
  WString key;
  while (get_CSV_WString(wifs, key)) {
    for (auto &s : set)
      if (!key.compare(s.label())) {
        size_t value;
        wifs >> value;
        s.set(s.begin() + value);
        break;
      }
    wifs.ignore(); // \n
  }
  wifs.close();
}

std::basic_istream<wchar_t> &
Data::get_CSV_WString(std::basic_istream<wchar_t> &is, Nostd::WString &s) {
  s = WString{};
  wchar_t input;
  while (!is.eof() && (input = is.get()) != Database::separator &&
         input != Database::newrecord) {
    s.push_back(input);
    if (s.back() == Database::escape)
      is.get(s.back());
  }
  return is;
}

std::basic_ostream<wchar_t> &
Data::put_CSV_WString(std::basic_ostream<wchar_t> &os,
                      const Nostd::WString &s) {
  for (auto x : s) {
    if (x == Database::separator || x == Database::newrecord)
      os << Database::escape;
    os << x;
  }
  return os;
}
