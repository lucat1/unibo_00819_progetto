/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Stefano Volpe #969766
  04/09/2021

  scenery.cpp: implementation of Data::Scenery and its helper entities.
*/

#include "scenery.hpp"

std::basic_istream<char> &Data::operator>>(std::basic_istream<char> &i,
                                           Scenery::Autotile &a) {
  if (i) {
    (i >> a.singlet).ignore();
    (i >> a.concave_top_left >> a.concave_top_right).ignore();
    (i >> a.concave_bottom_left >> a.concave_bottom_right).ignore();
    (i >> a.top_left >> a.top >> a.top_right).ignore();
    (i >> a.left >> a.center >> a.right).ignore();
    (i >> a.bottom_left >> a.bottom >> a.bottom_right).ignore();
    short foreground, background;
    (i >> foreground).ignore();
    (i >> background).ignore();
    a.foreground = Engine::short_to_color(foreground);
    a.background = Engine::short_to_color(background);
  }
  return i;
}

std::basic_istream<char> &Data::operator>>(std::basic_istream<char> &i,
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
