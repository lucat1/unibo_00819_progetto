#include "button.hpp"

#include <iostream>
using namespace std;

Engine::UI::Button::Button(uint16_t max_width, uint16_t max_height,
                           const wchar_t *content)
    : TextBox(max_width - 2, max_height - 2, content) {}
Engine::UI::Button::Button(uint16_t max_width, uint16_t max_height,
                           Nostd::WString &&content)
    : TextBox(max_width - 2, max_height - 2, content.c_str()) {}
Engine::UI::Button::~Button() {
  delwin(button_window);
  button_window = nullptr;
}

void Engine::UI::Button::show(WINDOW *window, uint16_t x, uint16_t y) {
  auto osize = TextBox::size();
  if (button_window != nullptr)
    delwin(button_window);

  button_window = subwin(window, osize.second + 2, osize.first + 2, x, y);
  if (bg != -1)
    wbkgd(button_window, bg);
  TextBox::show(button_window, 1, 1);
  wrefresh(window);
  wrefresh(button_window);
  cout << "drawn" << endl;
}
Nostd::Pair<uint16_t, uint16_t> Engine::UI::Button::size() {
  auto osize = TextBox::size();
  uint16_t width = osize.first + 2, height = osize.second + 2;
  return {width, height};
}
