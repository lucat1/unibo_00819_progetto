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

#include "../engine/colorable.hpp"
#include "map_chunk.hpp"
#include "pawns/hero.hpp"
#include "pawns/result.hpp"
#include "scenery.hpp"
#include "setting.hpp"

using namespace Data;
using namespace Data::Pawns;
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
  load_results();
  load_heroes(assets);
  // TODO
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
  res = move(d.res);
  her = move(d.her);
  // TODO
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
  her = move(d.her);
  res = move(d.res);
  // TODO
  return *this;
}

Database::Database(const Database &d) { *this = d; }

Database &Database::operator=(const Database &d) {
  conf = newstrcpy(d.conf);
  scor = newstrcpy(d.scor);
  set = d.set;
  map = d.map;
  sce = d.sce;
  res = d.res;
  her = d.her;
  // TODO
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
  for (auto x : res)
    put_CSV_WString(wofs, x.name()) << separator << x.score() << separator
                                    << Engine::color_to_short(x.foreground())
                                    << separator << x.character() << newrecord;
  wofs.close();
}

Nostd::UnorderedMap<Nostd::WString, Pawns::Hero> &Database::heroes() noexcept {
  return her;
}

const Nostd::UnorderedMap<Nostd::WString, Pawns::Hero> &
Database::heroes() const noexcept {
  return her;
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
  wifstream settings_wifs{settings_fp};
  delete settings_fp;
  Setting s;
  while (settings_wifs >> s)
    set.push_back(s);
  settings_wifs.close();
  // current values
  wifstream conf_wifs(conf);
  WString key;
  while (get_CSV_WString(conf_wifs, key)) {
    size_t value;
    conf_wifs >> value;
    for (auto &s : set)
      if (!key.compare(s.label())) {
        s.set(s.begin() + value);
        break;
      }
  }
  conf_wifs.close();
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
  WString name;
  while (get_CSV_WString(wifs, name)) {
    int score;
    short foreground;
    (wifs >> score).ignore();
    wchar_t character;
    (wifs >> foreground).ignore();
    (wifs >> character).ignore();
    res.push_back({name, score, Engine::short_to_color(foreground), character});
  }
}

void Database::load_heroes(const char *assets_filepath) {
  const char *const heroes_fp{newstrcat(assets_filepath, heroes_rel_fp)};
  wifstream wifs{heroes_fp};
  delete heroes_fp;
  Hero h{Engine::Color::transparent, L' ', L"", L"", {}, {}, 1, 1};
  while (wifs >> h) {
    her.put(h.name(), h);
  }
  wifs.close();
}

std::basic_istream<wchar_t> &
Data::get_CSV_WString(std::basic_istream<wchar_t> &is, WString &s) {
  if (is) {
    s = WString{};
    for (wchar_t input; is.get(input) && input != Database::separator &&
                        input != Database::newrecord;) {
      if (input == Database::escape) {
        if (is)
          is.get(input);
        else
          break; // escape character + EOF
      }
      s.push_back(input);
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
