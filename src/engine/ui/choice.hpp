/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Luca Tagliavini #971133
  04/8/2021

  choice.hpp: Defines Engine::UI::Choice visual component, which allows the user
  to perform a choice between the provided options
*/
#ifndef ENGINE_UI_CHOICE_HPP
#define ENGINE_UI_CHOICE_HPP

#include "../../data/setting.hpp"
#include "text_box.hpp"

namespace Engine {
namespace UI {
// Choice is a visual _interactable_ component which allows the user to choose
// from an array of options or from two (case: binary) values. It behaves as an
// usual component but draws colors differently. In fact, we use the
// background() color to draw text which is not selected, and foreground() to
// draw selected values.
//
// NOTE: a pointer to the setting must be passed to instantiate this class, but
// it worn't be freed when the Choice element is destroyed. It is a duty of the
// caller
class Choice : public Box {
private:
  Data::Setting *setting;
  bool boolean;
  uint16_t width;

public:
  Choice(uint16_t max_width, uint16_t max_height, Data::Setting *setting);

  void show(WINDOW *window, uint16_t x, uint16_t y);
  Nostd::Pair<uint16_t, uint16_t> size();
};

} // namespace UI
} // namespace Engine

#endif // ENGINE_UI_CHOICE_HPP
