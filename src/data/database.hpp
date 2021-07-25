/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Stefano Volpe #969766
  04/03/2021

  database.hpp: user interface of Data::Database and its helper entities.
*/

#ifndef DATA_DATABASE_HPP
#define DATA_DATABASE_HPP

#include <istream>
#include <ostream>

#include "../nostd/list.hpp"
#include "../nostd/string.hpp"
#include "../nostd/vector.hpp"
#include "map_chunk.hpp"
#include "pawns/enemy.hpp"
#include "pawns/hero.hpp"
#include "pawns/item.hpp"
#include "pawns/result.hpp"
#include "pawns/skill.hpp"
#include "scenery.hpp"
#include "setting.hpp"

namespace Data {

/*
  A Database collects every game object in an organized way. It is loaded from
  *non-standard* CSV and plain text files.
*/
class Database {
public:
  // Special characters used by CSV files
  constexpr static char separator{','}, newrecord{'\n'}, escape{'\\'};
  // Relative filepaths for various kind of resources
  constexpr const static char *const settings_rel_fp{"/csv/settings.csv"},
      *const maps_rel_fp{"/img/maps.txt"},
          *const sceneries_rel_fp{"/img/sceneries.txt"},
              *const heroes_rel_fp{"/csv/heroes.csv"},
                  *const mugshots_rel_fp{"/img/heroes.txt"},
                      *const enemies_rel_fp{"/csv/enemies.csv"},
                          *const items_rel_fp{"/csv/items.csv"},
                              *const audio_rel_fp{"/audio/"};

  Database() = delete; // cannot constructs a database from nothing
  // Each parameter is a relative filepath:
  // 1) configuration: user settings CSV file
  // 2) assets: main assets folder
  // 3) scoreboard: CSV file containing sorted previous high scores
  Database(const char *configuration, const char *assets,
           const char *scoreboard);
  Database(Database &&);
  Database &operator=(Database &&);
  Database(const Database &);
  Database &operator=(const Database &);

  ~Database();

  Nostd::Vector<Setting> &settings() noexcept; // gets game settings
  const Nostd::Vector<Setting> &settings() const noexcept;
  void save_settings() const; // saves current setting values to filesystem

  Nostd::Vector<MapChunk> &map_chunks() noexcept; // gets map chunks for World
  const Nostd::Vector<MapChunk> &map_chunks() const noexcept;

  Nostd::Vector<Scenery> &sceneries() noexcept; // gets game sceneries for World
  const Nostd::Vector<Scenery> &sceneries() const noexcept;

  Nostd::List<Pawns::Result> &results() noexcept; // gets game high scores
  const Nostd::List<Pawns::Result> &results() const noexcept;
  void save_results() const; // saves current high scores to filesystem

  Nostd::Vector<Pawns::Hero> &heroes() noexcept; // gets playable heroes
  const Nostd::Vector<Pawns::Hero> &heroes() const noexcept;

  Nostd::Vector<Pawns::Enemy> &enemies() noexcept; // gets species of enemies
  const Nostd::Vector<Pawns::Enemy> &enemies() const noexcept;

  Nostd::Vector<Pawns::Item> &items() noexcept; // gets species of items
  const Nostd::Vector<Pawns::Item> &items() const noexcept;

  // Converts an audio filename to its relative filepath:
  // - adds subfolder path
  // - does not add file extension
  char *to_audio_filepath(const char *audio_filename) const noexcept;

private:
  char *conf, *scor;
  Nostd::Vector<Setting> set{};
  Nostd::Vector<MapChunk> map{};
  Nostd::Vector<Scenery> sce{};
  Nostd::List<Pawns::Result> res{};
  Nostd::Vector<Pawns::Hero> her{};
  Nostd::Vector<Pawns::Enemy> ene{};
  Nostd::Vector<Pawns::Item> ite{};

  char *newstrcpy(const char *) const;
  char *newstrcat(const char *, const char *) const;
  void load_settings(const char *assets_filepath);
  void load_map_chunks(const char *assets_filepath);
  void load_sceneries(const char *assets_filepath);
  void load_results();
  void load_heroes(const char *assets_filepath);
  void load_mugshots(const char *assets_filepath);
  void load_enemies(const char *assets_filepath);
  void load_items(const char *assets_filepath);
};

// Gets a "string" value from an input stream in CSV format
std::basic_istream<char> &get_CSV_String(std::basic_istream<char> &,
                                         Nostd::String &);

// Puts a "string" value into an output stream in CSV format
std::basic_ostream<char> &put_CSV_String(std::basic_ostream<char> &,
                                         const Nostd::String &);

} // namespace Data

#endif
