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
#include "../screen.hpp"
#include "../utils.hpp"
#include <ncurses.h>

using Engine::Utils::digits;
using Engine::Utils::stringify;

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
  int color_on = Screen::color_pair(fg, color_to_short(parent->background())),
      color_off = Screen::color_pair(bg, color_to_short(parent->background()));

  if (boolean) {
    bool on = *setting->current_value() == 1;
    Screen::start_color(window, color_off);
    mvwaddstr(window, y, x, "<");
    Screen::end_color(window, color_off);

    Screen::start_color(window, !on ? color_on : color_off);
    mvwaddstr(window, y, x + 2, "off");
    Screen::end_color(window, !on ? color_on : color_off);

    Screen::start_color(window, color_off);
    mvwaddstr(window, y, x + 6, "/");
    Screen::end_color(window, color_off);

    Screen::start_color(window, on ? color_on : color_off);
    mvwaddstr(window, y, x + 8, "on");
    Screen::end_color(window, on ? color_on : color_off);

    Screen::start_color(window, color_off);
    mvwaddstr(window, y, x + 11, ">");
    Screen::end_color(window, color_off);
  } else {
    szu next_x = x + 2 * digits(setting->last()) + 2;

    Screen::start_color(window, color_on);
    Nostd::String str;
    stringify(*setting->current_value(), str);
    str.push_back(u'/');
    stringify(setting->last(), str);
    str.push_back(u' ');
    mvwaddstr(window, y, x, str.c_str());
    Screen::end_color(window, color_on);

    // val : 10 = max : min
    int val = (10 * *setting->current_value()) / setting->last();

    Screen::start_color(window, color_off);
    mvwaddch(window, y, next_x, '<');
    Screen::end_color(window, color_off);

    Screen::start_color(window, color_on);
    for (int i = 0; i < val; i++)
      mvwaddch(window, y, next_x + 1 + i, '=');
    Screen::end_color(window, color_on);
    Screen::start_color(window, color_off);
    for (int i = val; i <= 10; i++)
      mvwaddch(window, y, next_x + 1 + i, '=');
    Screen::end_color(window, color_off);

    Screen::start_color(window, color_off);
    mvwaddch(window, y, next_x + 11, '>');
    Screen::end_color(window, color_off);
  }
}

Engine::UI::Box::dim Engine::UI::Choice::size(szu max_width, szu max_height) {
  return {fr ? max_width : width, 1};
}
