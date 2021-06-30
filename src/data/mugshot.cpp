/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Stefano Volpe #969766
  06/23/2021

  mugshot.cpp: implementation of Data::Mugshot and its helper entities.
*/

#include "mugshot.hpp"

#include "../engine/block_tile.hpp"

using namespace Engine;
using Data::Mugshot;
using Nostd::Matrix;

Mugshot::Mugshot() : Matrix<const Tile *>({side, side}, nullptr) {}

Mugshot::Mugshot(const Mugshot &m) : Matrix<const Tile *>(m) {
  for (auto row : *this)
    for (auto cell : row) {
      auto &v = cell.value();
      v = new BlockTile{v->character(), v->foreground(), v->background()};
    }
}

Mugshot &Mugshot::operator=(const Mugshot &m) {
  Matrix<const Tile *>::operator=(m);
  for (auto row : *this)
    for (auto cell : row) {
      auto &v = cell.value();
      delete v;
      v = new BlockTile{v->character(), v->foreground(), v->background()};
    }
  return *this;
}

Mugshot::~Mugshot() {
  if (Matrix<const Tile *>::size())
    for (auto row : *this)
      for (auto cell : row) {
        delete cell.value();
        cell.value() = nullptr;
      }
}

std::basic_istream<wchar_t> &Data::operator>>(std::basic_istream<wchar_t> &is,
                                              Mugshot &m) {
  Matrix<wchar_t> characters({m.side, m.side});
  for (auto &row : characters) {
    for (auto &cell : row)
      is.get(cell.value());
    is.ignore();
  }
  Matrix<short> foregrounds({m.side, m.side});
  for (auto &row : foregrounds)
    for (auto &cell : row)
      is >> cell.value();
  Matrix<short> backgrounds({m.side, m.side});
  for (auto &row : backgrounds)
    for (auto &cell : row)
      is >> cell.value();
  // Put everything together
  for (size_t i{0}; i < m.side; ++i)
    for (size_t j{0}; j < m.side; ++j)
      m.at(i).at(j).value() = new BlockTile(
          characters.at(i).at(j).value(),
          Engine::short_to_color(foregrounds.at(i).at(j).value()),
          Engine::short_to_color(backgrounds.at(i).at(j).value()));
  return is;
}
