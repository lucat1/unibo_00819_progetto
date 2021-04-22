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
#include "../nostd/unordered_map.hpp"
#include "../nostd/vector.hpp"
#include "../nostd/wstring.hpp"
#include "map_chunk.hpp"
#include "result.hpp"
#include "scenery.hpp"
#include "setting.hpp"

namespace Data {

/*
  A Database collects every game object in an organized way. It is loaded from
  *non-standard* CSV, INI and plain text files.
*/
class Database {
public:
  constexpr static wchar_t separator{','}, newrecord{'\n'}, escape{'\\'};
  constexpr const static char *const settings_rel_fp{"/csv/settings.csv"},
      *const maps_rel_fp{"/maps.txt"},
          *const sceneries_rel_fp{"/sceneries.txt"};

  Database() = delete; // cannot constructs a database from nothing
  Database(const char *configuration, const char *assets,
           const char *scoreboard);
  Database(Database &&) = default;
  Database &operator=(Database &&) = default;
  Database(const Database &) = default;
  Database &operator=(const Database &) = default;

  ~Database();

  Nostd::Vector<Setting> &settings() noexcept;
  const Nostd::Vector<Setting> &settings() const noexcept;
  void save_settings() const; // saves current setting values to filesystem

  Nostd::Vector<MapChunk> &map_chunks() noexcept;
  const Nostd::Vector<MapChunk> &map_chunks() const noexcept;

  Nostd::Vector<Scenery> &sceneries() noexcept;
  const Nostd::Vector<Scenery> &sceneries() const noexcept;

  // TODO

  Nostd::List<Result> &results() noexcept;
  const Nostd::List<Result> &results() const noexcept;
  void save_results() const; // saves current high scores to filesystem

private:
  char *conf, *scor;
  Nostd::Vector<Setting> set{};
  Nostd::Vector<MapChunk> map{};
  Nostd::Vector<Scenery> sce{};
  // TODO
  Nostd::UnorderedMap<Nostd::WString, Interactables::Hero> her{};
  // TODO
  Nostd::List<Result> res{};

  char *newstrcpy(const char *) const;
  char *newstrcat(const char *, const char *) const;
  void load_settings(const char *assets_filepath);
  void load_map_chunks(const char *assets_filepath);
  void load_sceneries(const char *assets_filepath);
  // TODO
  void load_results();
};

std::basic_istream<wchar_t> &get_CSV_WString(std::basic_istream<wchar_t> &,
                                             Nostd::WString &);

std::basic_ostream<wchar_t> &put_CSV_WString(std::basic_ostream<wchar_t> &,
                                             const Nostd::WString &);

} // namespace Data

#endif
