/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Stefano Volpe #969766
  06/23/2021

  mugshot.cpp: implementation of Data::Mugshot and its helper entities.
*/

#include "mugshot.hpp"

using Data::MugshotTile;

MugshotTile::MugshotTile(Engine::Color foreground, Engine::Color background,
                         wchar_t character)
    : fg{foreground}, bg{background}, chr{character} {}

Engine::Color MugshotTile::foreground() const noexcept { return fg; }

Engine::Color MugshotTile::background() const noexcept { return bg; }

wchar_t MugshotTile::character() const noexcept { return chr; }

bool MugshotTile::operator==(MugshotTile m) const noexcept {
  return fg == m.fg && bg == m.bg && chr == m.chr;
}

bool MugshotTile::operator!=(MugshotTile m) const noexcept {
  return !(*this == m);
}

std::basic_istream<wchar_t> &Data::operator>>(std::basic_istream<wchar_t> &is,
                                              MugshotTile &m) {
  short foreground, background;
  wchar_t character;
  (is >> foreground >> background).ignore();
  if (is >> character)
    m = MugshotTile(Engine::short_to_color(foreground),
                    Engine::short_to_color(background), character);
  return is;
}

std::basic_ostream<wchar_t> &operator<<(std::basic_ostream<wchar_t> &os,
                                        MugshotTile m) {
  return os << m.character();
}

Data::Mugshot::Mugshot()
    : Nostd::Matrix<MugshotTile>({side, side}, MugshotTile{}) {}

std::basic_istream<wchar_t> &Data::operator>>(std::basic_istream<wchar_t> &is,
                                              Data::Mugshot &m) {
  Nostd::Matrix<wchar_t> characters({m.side, m.side});
  for (auto &row : characters) {
    for (auto &cell : row)
      is.get(cell.value());
    is.ignore();
  }
  Nostd::Matrix<short> foregrounds({m.side, m.side});
  for (auto &row : foregrounds)
    for (auto &cell : row)
      is >> cell.value();
  Nostd::Matrix<short> backgrounds({m.side, m.side});
  for (auto &row : backgrounds)
    for (auto &cell : row)
      is >> cell.value();
  for (size_t i{0}; i < m.side; ++i)
    for (size_t j{0}; j < m.side; ++j)
      m.at(i).at(j).value() =
          MugshotTile(Engine::short_to_color(foregrounds.at(i).at(j).value()),
                      Engine::short_to_color(backgrounds.at(i).at(j).value()),
                      characters.at(i).at(j).value());
  return is;
}
