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
#include <utility>

#include "map_chunk.hpp"
#include "result.hpp"
#include "scenery.hpp"
#include "setting.hpp"

using namespace Data;
using Nostd::List;
using Nostd::Vector;
using Nostd::WString;
using std::ifstream;
using std::wifstream;

constexpr wchar_t Database::separator, Database::newrecord, Database::escape;

Database::Database(const char *configuration, const char *assets,
                   const char *scoreboard)
    : conf{newstrcpy(configuration)}, scor{newstrcpy(scoreboard)} {
  load_settings(assets);
  load_map_chunks(assets);
  load_sceneries(assets);
  // TODO
  load_results();
}

Database::Database(Database &&d) {
  conf = d.conf;
  d.conf = nullptr;
  scor = d.scor;
  d.scor = nullptr;
  using std::move;
  set = move(d.set);
  map = move(d.map);
  sce = move(d.sce);
  // TODO
  her = move(d.her);
  // TODO
  res = move(d.res);
}

Database &Database::operator=(Database &&d) {
  delete conf;
  conf = d.conf;
  d.conf = nullptr;
  delete scor;
  scor = d.scor;
  d.scor = nullptr;
  using std::move;
  set = move(d.set);
  map = move(d.map);
  sce = move(d.sce);
  // TODO
  her = move(d.her);
  // TODO
  res = move(d.res);
  return *this;
}

Database::Database(const Database &d) { *this = d; }

Database &Database::operator=(const Database &d) {
  conf = newstrcpy(d.conf);
  scor = newstrcpy(d.scor);
  set = d.set;
  map = d.map;
  sce = d.sce;
  // TODO
  her = d.her;
  // TODO
  res = d.res;
  return *this;
}

Database::~Database() {
  delete conf;
  delete scor;
}

Vector<Setting> &Database::settings() noexcept { return set; }

const Vector<Setting> &Database::settings() const noexcept { return set; }

void Database::save_settings() const {
  std::wofstream wofs(conf);
  for (auto x : set)
    wofs << x << newrecord;
  wofs.close();
}

Vector<MapChunk> &Database::map_chunks() noexcept { return map; }

const Vector<MapChunk> &Database::map_chunks() const noexcept { return map; }

Vector<Scenery> &Database::sceneries() noexcept { return sce; }

const Vector<Scenery> &Database::sceneries() const noexcept { return sce; }

List<Result> &Database::results() noexcept { return res; }

const List<Result> &Database::results() const noexcept { return res; }

void Database::save_results() const {
  std::wofstream wofs(scor);
  for (auto x : res) {
    put_CSV_WString(wofs, x.nickname()) << separator;
    if (x.hero())
      put_CSV_WString(wofs, x.hero()->name());
    wofs << separator;
    wofs << x.score() << newrecord;
  }
  wofs.close();
}

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
  wifstream wifs{settings_fp};
  delete settings_fp;
  Setting s;
  while (wifs >> s)
    set.push_back(s);
  wifs.close();
  // current values
  wifs.open(conf);
  WString key;
  while (get_CSV_WString(wifs, key)) {
    size_t value;
    wifs >> value;
    wchar_t input;
    while (wifs >> input && input != newrecord)
      ;
    for (auto &s : set)
      if (!key.compare(s.label())) {
        s.set(s.begin() + value);
        break;
      }
  }
  wifs.close();
}

void Database::load_map_chunks(const char *assets_filepath) {
  const char *const maps_fp{newstrcat(assets_filepath, maps_rel_fp)};
  ifstream ifs{maps_fp};
  delete maps_fp;
  MapChunk m(0, 0, 0);
  while (ifs >> m)
    map.push_back(m);
  ifs.close();
}

void Database::load_sceneries(const char *assets_filepath) {
  const char *const sceneries_fp{newstrcat(assets_filepath, sceneries_rel_fp)};
  wifstream wifs{sceneries_fp};
  delete sceneries_fp;
  Scenery s;
  while (wifs >> s)
    sce.push_back(s);
  wifs.close();
}

void Database::load_results() {
  wifstream wifs{scor};
  WString nickname;
  while (get_CSV_WString(wifs, nickname)) {
    WString hero;
    int score;
    get_CSV_WString(wifs, hero) >> score;
    res.push_back(
        {nickname, her.contains(nickname) ? &her[nickname] : nullptr, score});
    wifs.ignore();
  }
}

std::basic_istream<wchar_t> &
Data::get_CSV_WString(std::basic_istream<wchar_t> &is, WString &s) {
  if (is) {
    s = WString{};
    wchar_t input;
    while (is >> input && input != Database::separator &&
           input != Database::newrecord) {
      s.push_back(input);
      if (s.back() == Database::escape)
        is >> s.back();
    }
  }
  return is;
}

std::basic_ostream<wchar_t> &
Data::put_CSV_WString(std::basic_ostream<wchar_t> &os,
                      const Nostd::WString &s) {
  for (auto x = s.cbegin(); x + 1 != s.end(); ++x) {
    if (*x == Database::separator || *x == Database::newrecord)
      os << Database::escape;
    os << *x;
  }
  return os;
}
