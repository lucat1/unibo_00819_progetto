/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Luca Tagliavini #971133
  04/8/2021

  choice.cpp: Implements the Engine::UI::Choice component drawing content by
  hand, as we change quite a few behaviors from the standard Engine::UI::TextBox
*/

#include "choice.hpp"

// returns the amount of digits needed to display an integer
inline int digits(int n) {
  int k = 0;
  while (n /= 10 > 0)
    k++;
  return k;
}

Engine::UI::Choice::Choice(Data::Setting *setting) : Box() {
  if (setting->first() == 0 && setting->last() == 1 && setting->stride() == 1)
    boolean = true;

  // !boolean: min/max <==========> OR
  // twice the min/max + 14 for all other chars
  // boolean: " < on / off > " = 14 (2 spaces)
  this->width = boolean ? 12 : 2 * digits(setting->last()) + 14;
  this->setting = setting;
}

void Engine::UI::Choice::show(WINDOW *window, szu abs_x, szu y, szu max_width,
                              szu max_height) {
  szu x = abs_x + (fr ? max_width - width : 0);
  int color_on = UI::color_pair(fg, bg), color_off = UI::color_pair(bg, fg);

  if (boolean) {
    bool on = *setting->current_value();
    mvwaddwstr(window, y, x, L"< ");

    UI::start_color(window, on ? color_on : color_off);
    mvwaddwstr(window, y, x + 2, L"on");
    UI::end_color(window, on ? color_on : color_off);

    mvwaddwstr(window, y, x + 4, L" / ");

    UI::start_color(window, !on ? color_on : color_off);
    mvwaddwstr(window, y, x + 7, L"off");
    UI::end_color(window, !on ? color_on : color_off);

    mvwaddwstr(window, y, x + 10, L" >");
  }

  /* mvwaddwstr(window, y + i, x + (fr ? max_width - line.length() : 0), */
  /*            line.c_str()); */
}

Nostd::Pair<uint16_t, uint16_t> Engine::UI::Choice::size(szu max_width,
                                                         szu max_height) {
  return {fr ? max_width : width, 1};
}
