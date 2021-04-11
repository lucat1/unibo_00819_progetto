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
#include <curses.h>

// returns the amount of digits needed to display an integer
inline int digits(int n) {
  int k = 0;
  while (n > 0) {
    k++;
    n /= 10;
  }

  return k;
}

// converts a number between 0 and 9 (inclusive) to a wchar_t charter
wchar_t digitize(int n) {
  if (n > 9)
    return L'-'; // undefined behaviour

  return L'0' + n;
}

// puts the given number in digits inside the provided WString
void stringify(int n, Nostd::WString &str) {
  int last = str.length();
  while (n > 0) {
    str.insert(last, digitize(n % 10));
    n /= 10;
  }
}

Engine::UI::Choice::Choice(Data::Setting *setting) : Box() {
  if (setting->first() == 0 && setting->last() == 1 && setting->stride() == 1)
    boolean = true;

  // !boolean: val/max <==========> OR
  // twice the val/max + 14 for all other chars
  // boolean: " < on / off > " = 12 (2 spaces)
  this->width = boolean ? 12 : 2 * digits(setting->last()) + 14;
  this->setting = setting;
}

Data::Setting *Engine::UI::Choice::get_setting() { return setting; }

// thanks to ncurses's color_pair(s), which turns out are just a huge
// technical debt (https://softwareengineering.stackexchange.com/a/336063) from
// the late '70s, we must always have to respecify the the background color in
// each color pair, and therefore we not only assue that the node has a parent
// from which we can take that color, but we also end up having an hilarious
// amount of calls to start_color and end_color to begin and end the coloring
// process for each couple of chars.
void Engine::UI::Choice::show(WINDOW *window, szu abs_x, szu y, szu max_width,
                              szu max_height) {
  szu x = abs_x + (fr ? max_width - width : 0);
  int color_on = UI::color_pair(fg, color_to_short(parent->background())),
      color_off = UI::color_pair(bg, color_to_short(parent->background()));

  if (boolean) {
    bool on = *setting->current_value() == 1;
    UI::start_color(window, color_off);
    mvwaddwstr(window, y, x, L"<");
    UI::end_color(window, color_off);

    UI::start_color(window, !on ? color_on : color_off);
    mvwaddwstr(window, y, x + 2, L"off");
    UI::end_color(window, !on ? color_on : color_off);

    UI::start_color(window, color_off);
    mvwaddwstr(window, y, x + 6, L"/");
    UI::end_color(window, color_off);

    UI::start_color(window, on ? color_on : color_off);
    mvwaddwstr(window, y, x + 8, L"on");
    UI::end_color(window, on ? color_on : color_off);

    UI::start_color(window, color_off);
    mvwaddwstr(window, y, x + 11, L">");
    UI::end_color(window, color_off);
  } else {
    szu next_x = x + 2 * digits(setting->last()) + 2;

    UI::start_color(window, color_on);
    Nostd::WString str;
    stringify(*setting->current_value(), str);
    str.push_back(L'/');
    stringify(setting->last(), str);
    str.push_back(L' ');
    mvwaddwstr(window, y, x, str.c_str());
    UI::end_color(window, color_on);

    // val : 10 = max : min
    int val = (10 * *setting->current_value()) / setting->last();

    UI::start_color(window, color_off);
    mvwaddch(window, y, next_x, '<');
    UI::end_color(window, color_off);

    UI::start_color(window, color_on);
    for (int i = 0; i < val; i++)
      mvwaddch(window, y, next_x + 1 + i, '=');
    UI::end_color(window, color_on);
    UI::start_color(window, color_off);
    for (int i = val; i <= 10; i++)
      mvwaddch(window, y, next_x + 1 + i, '=');
    UI::end_color(window, color_off);

    UI::start_color(window, color_off);
    mvwaddch(window, y, next_x + 11, '>');
    UI::end_color(window, color_off);
  }
}

Engine::UI::Box::dim Engine::UI::Choice::size(szu max_width, szu max_height) {
  return {fr ? max_width : width, 1};
}
