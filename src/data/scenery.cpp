/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Stefano Volpe #969766
  04/09/2021

  scenery.cpp: implementation of Data::Scenery.
*/

#include "scenery.hpp"

std::basic_istream<wchar_t> &Data::operator>>(std::basic_istream<wchar_t> &i,
                                              Scenery::Autotile &a) {
  if (i) {
    i >> a.singlet;
    i.ignore();
    i >> a.concave_top_left >> a.concave_top_right;
    i.ignore();
    i >> a.concave_bottom_left >> a.concave_bottom_right;
    i.ignore();
    i >> a.top_left >> a.top >> a.top_right;
    i.ignore();
    i >> a.left >> a.center >> a.right;
    i.ignore();
    i >> a.bottom_left >> a.bottom >> a.bottom_right;
    i.ignore();
    short foreground, background;
    i >> foreground;
    i.ignore();
    i >> background;
    a.foreground = Engine::short_to_color(foreground);
    a.background = Engine::short_to_color(background);
    i.ignore();
  }
  return i;
}

std::basic_istream<wchar_t> &Data::operator>>(std::basic_istream<wchar_t> &i,
                                              Scenery &s) {
  if (i >> s.ground) {
    i >> s.platform;
    size_t sky_colors;
    i >> sky_colors;
    i.ignore();
    s.sky = Nostd::Vector<Engine::Color>(sky_colors);
    for (auto &x : s.sky) {
      short color_code;
      i >> color_code;
      i.ignore();
      x = Engine::short_to_color(color_code);
    }
  }
  return i;
};
