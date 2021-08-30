/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Luca Tagliavini #971133
  07/02/2021

  hud.hpp: Implements the HUD (Head Up Display) for the whole game scene
*/

#include "hud.hpp"
#include "../../data/palette.hpp"
#include "../screen.hpp"
#include "../ui/text_box.hpp"
#include "../utils.hpp"
#include <cstring>

Engine::Scene::HUD::HUD(const Data::Pawns::Hero &player,
                        const Nostd::String &message)
    : player{player}, message{message} {}

void Engine::Scene::HUD::bar(WINDOW *window, szu x, szu y, int value,
                             int max_value, const char icon[5], Color c) {
  int pair = Screen::color_pair(color_to_short(Data::Palette::unfocused),
                                color_to_short(c)),
      pairi = Screen::color_pair(color_to_short(c),
                                 color_to_short(Data::Palette::unfocused));

  int mid =
      ((float)value / max_value) * 9; // value percentage drawn in 9 char cells
  int icon_pair =
      Screen::color_pair(color_to_short(c), color_to_short(Color::black));
  Screen::start_color(window, icon_pair);
  mvwaddstr(window, y, x, icon);
  x = x + 3; // hardcoded as strlen doesn't give proper output on unicode chars

  for (int i = 0; i < 9; i++) {
    Screen::start_color(window, i < mid ? pair : pairi);
    if (i < 2) {
      mvwaddch(window, y, x + i, ' ');
    } else if (i == 2 && value > 9) {
      // displayed only when the value has 2 digits
      mvwaddch(window, y, x + i, Utils::digitize(value / 10));
    } else if (i == 3) {
      mvwaddch(window, y, x + i, Utils::digitize(value % 10));
    } else if (i == 4) {
      mvwaddch(window, y, x + i, '/');
    } else if (i == 5) {
      // when the max_value has only one digit we display the first one here,
      // and nothing in the next position
      mvwaddch(
          window, y, x + i,
          Utils::digitize(max_value > 9 ? max_value / 10 : max_value % 10));
    } else if (i == 6 && max_value > 9) {
      mvwaddch(window, y, x + i, Utils::digitize(max_value % 10));
    } else {
      mvwaddch(window, y, x + i, ' ');
    }
    Screen::end_color(window, i < mid ? pair : pairi);
  }
}

// show creates a new root of components from the Engine::UI namespace which
// will be shown as the HUD visual interface
void Engine::Scene::HUD::show(WINDOW *window, szu x, szu y, szu max_width,
                              szu max_height) {
  bar(window, x, y, player.current_health(), player.max_health(), " ♡ ",
      Data::Palette::health);
  bar(window, x + 12, y, player.current_mana(), player.max_mana(), " ↑ ",
      Data::Palette::mana);
  Nostd::String scr = " ● ";
  Utils::stringify(player.score(), scr);
  scr.append("   ");
  scr.append(message);
  mvwaddstr(window, x + 24, y, scr.c_str());
}

// we're going to display the HUD in one single line on the bottom of the screen
Engine::UI::Box::dim Engine::Scene::HUD::size(szu max_width, szu max_height) {
  return {Screen::columns, 1};
}
