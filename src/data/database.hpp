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

#include "../nostd/vector.hpp"
#include "../nostd/wstring.hpp"
#include "map.hpp"
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
  constexpr static wchar_t separator{','}, newline{'\n'}, escape{'\\'},
      newline_escape{'n'};

  Database() = delete;            // cannot constructs a database from nothing
  Database(const char *filename); // loads from the filesystem
  Database(Database &&) = default;
  Database &operator=(Database &&) = default;
  Database(const Database &) = default;
  Database &operator=(const Database &) = default;

  Nostd::Vector<Result> &results() noexcept;
  const Nostd::Vector<Result> &results() const noexcept;
  void save_results() const; // saves current high scores to filesystem

  Nostd::Vector<Setting> &settings() noexcept;
  const Nostd::Vector<Setting> &settings() const noexcept;
  void save_settings() const; // saves current setting values to filesystem

  Nostd::Vector<Map> &maps() noexcept;
  const Nostd::Vector<Map> &maps() const noexcept;

  Nostd::Vector<Scenery> &sceneries() noexcept;
  const Nostd::Vector<Scenery> &sceneries() const noexcept;
};

std::basic_istream<wchar_t> &get_CSV_WString(std::basic_istream<wchar_t> &,
                                             Nostd::WString &);

std::basic_ostream<wchar_t> &put_CSV_WString(std::basic_ostream<wchar_t> &,
                                             const Nostd::WString &);

} // namespace Data

#endif
