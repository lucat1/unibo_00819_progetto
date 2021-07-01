/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Stefano Volpe #969766
  06/23/2021

  mugshot.cpp: implementation of Data::Mugshot and its helper entities.
*/

#include "mugshot.hpp"

using Data::Mugshot;
using Engine::Color;
using Nostd::Matrix;

Mugshot::Mugshot() : Matrix<Color>({height, width}, Color::transparent) {}

std::basic_istream<wchar_t> &Data::operator>>(std::basic_istream<wchar_t> &is,
                                              Mugshot &m) {
  for (auto &row : m)
    for (auto &cell : row) {
      short input;
      is >> input;
      cell.value() = Engine::short_to_color(input);
    }
  return is;
}
