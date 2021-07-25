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
#include <stdexcept>
#include <utility>

#include "../engine/colorable.hpp"
#include "map_chunk.hpp"
#include "pawns/enemy.hpp"
#include "pawns/hero.hpp"
#include "pawns/item.hpp"
#include "pawns/result.hpp"
#include "scenery.hpp"
#include "setting.hpp"

using namespace Data;
using namespace Data::Pawns;
using Nostd::List;
using Nostd::String;
using Nostd::Vector;
using std::ifstream;

constexpr char Database::separator, Database::newrecord, Database::escape;

Database::Database(const char *configuration, const char *assets,
                   const char *scoreboard)
    : conf{newstrcpy(configuration)}, scor{newstrcpy(scoreboard)} {
  load_settings(assets);
  load_map_chunks(assets);
  load_sceneries(assets);
  load_results();
  load_heroes(assets);
  load_mugshots(assets);
  load_enemies(assets);
  load_items(assets);
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
  ene = move(d.ene);
  ite = move(d.ite);
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
  res = move(d.res);
  her = move(d.her);
  ene = move(d.ene);
  ite = move(d.ite);
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
  ene = d.ene;
  ite = d.ite;
  return *this;
}

Database::~Database() {
  delete conf;
  delete scor;
}

Vector<Setting> &Database::settings() noexcept { return set; }

const Vector<Setting> &Database::settings() const noexcept { return set; }

void Database::save_settings() const {
  std::ofstream ofs(conf);
  for (auto x : set)
    ofs << x << newrecord;
  ofs.close();
}

Vector<MapChunk> &Database::map_chunks() noexcept { return map; }

const Vector<MapChunk> &Database::map_chunks() const noexcept { return map; }

Vector<Scenery> &Database::sceneries() noexcept { return sce; }

const Vector<Scenery> &Database::sceneries() const noexcept { return sce; }

List<Result> &Database::results() noexcept { return res; }

const List<Result> &Database::results() const noexcept { return res; }

void Database::save_results() const {
  std::ofstream ofs(scor);
  for (auto x : res)
    put_CSV_String(ofs, x.name()) << separator << x.score() << separator
                                  << Engine::color_to_short(x.foreground())
                                  << separator << x.character() << newrecord;
  ofs.close();
}

Nostd::Vector<Pawns::Hero> &Database::heroes() noexcept { return her; }

const Nostd::Vector<Pawns::Hero> &Database::heroes() const noexcept {
  return her;
}

Nostd::Vector<Pawns::Enemy> &Database::enemies() noexcept { return ene; }

const Nostd::Vector<Pawns::Enemy> &Database::enemies() const noexcept {
  return ene;
}

Nostd::Vector<Pawns::Item> &Database::items() noexcept { return ite; }

const Nostd::Vector<Pawns::Item> &Database::items() const noexcept {
  return ite;
}

char *Database::to_audio_filepath(const char *audio_filename) const noexcept {
  return newstrcat(audio_rel_fp, audio_filename);
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
  ifstream settings_ifs{settings_fp};
  delete settings_fp;
  Setting s;
  while (settings_ifs >> s)
    set.push_back(s);
  settings_ifs.close();
  // current values
  ifstream conf_ifs(conf);
  String key;
  while (get_CSV_String(conf_ifs, key)) {
    size_t value;
    conf_ifs >> value;
    for (auto &s : set)
      if (!key.compare(s.label())) {
        s.set(s.begin() + value);
        break;
      }
  }
  conf_ifs.close();
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
  ifstream ifs{sceneries_fp};
  delete sceneries_fp;
  Scenery s;
  while (ifs >> s)
    sce.push_back(s);
  ifs.close();
}

void Database::load_results() {
  ifstream ifs{scor};
  String name;
  while (get_CSV_String(ifs, name)) {
    int score;
    (ifs >> score).ignore();
    short foreground;
    char character;
    (ifs >> foreground).ignore();
    if (ifs >> character) {
      res.push_back(
          {name, character, Engine::short_to_color(foreground), score});
      ifs.ignore();
    }
  }
}

void Database::load_heroes(const char *assets_filepath) {
  const char *const heroes_fp{newstrcat(assets_filepath, heroes_rel_fp)};
  ifstream ifs{heroes_fp};
  delete heroes_fp;
  Hero h{Engine::Color::transparent, u' ', "", "", {}, {}, 1, 1};
  while (ifs >> h)
    her.push_back(h);
  ifs.close();
}

void Database::load_mugshots(const char *assets_filepath) {
  const char *const mugshots_fp{newstrcat(assets_filepath, mugshots_rel_fp)};
  ifstream ifs{mugshots_fp};
  delete mugshots_fp;
  for (auto &x : her) {
    if (!ifs)
      throw std::length_error("Not enough mugshots.");
    ifs >> x.mugshot();
  }
  ifs.close();
}

void Database::load_enemies(const char *assets_filepath) {
  const char *const enemies_fp{newstrcat(assets_filepath, enemies_rel_fp)};
  ifstream ifs{enemies_fp};
  delete enemies_fp;
  Enemy e{Engine::Color::transparent, u' ', "", {}, 0, 0, 0, 1};
  while (ifs >> e)
    ene.push_back(e);
  ifs.close();
}

void Database::load_items(const char *assets_filepath) {
  const char *const items_fp{newstrcat(assets_filepath, items_rel_fp)};
  ifstream ifs{items_fp};
  delete items_fp;
  Item i{Engine::Color::transparent, u' ', "", 0, false, 0, false, 0};
  while (ifs >> i)
    ite.push_back(i);
  ifs.close();
}

std::basic_istream<char> &Data::get_CSV_String(std::basic_istream<char> &is,
                                               String &s) {
  if (is) {
    s = String{};
    for (char input; is.get(input) && input != Database::separator &&
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

std::basic_ostream<char> &Data::put_CSV_String(std::basic_ostream<char> &os,
                                               const Nostd::String &s) {
  for (auto x = s.cbegin(); x + 1 != s.end(); ++x) {
    if (*x == Database::separator || *x == Database::newrecord)
      os << Database::escape;
    os << *x;
  }
  return os;
}
