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

std::basic_istream<wchar_t> &operator>>(std::basic_istream<wchar_t> &is,
                                        MugshotTile &m) {
  short foreground, background;
  wchar_t character;
  if (is >> foreground >> background >> character)
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
