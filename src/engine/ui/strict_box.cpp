/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Luca Tagliavini #971133
  07/01/2021

  strict_box.cpp: Implements a version of Box which allows the consumer to
  focefully define absolute maximum dimentions, withing which the children must
  fit
*/

#include "strict_box.hpp"
#include <algorithm>

Engine::UI::StrictBox::StrictBox(Box::dim max_dimentions) {
  this->absolute_max_width = max_dimentions.first;
  this->absolute_max_height = max_dimentions.second;
}

Engine::UI::Box::dim Engine::UI::StrictBox::size(szu max_width,
                                                 szu max_height) {
  szu width = std::min(absolute_max_width, max_width);
  szu height = std::min(absolute_max_height, max_width);
  return Box::size(width, height);
}
