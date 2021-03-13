#ifndef TEXT_BOX_HPP
#define TEXT_BOX_HPP

#include "box.hpp"
#include <ncurses.h>
#include <vector>
using namespace std;

namespace Engine {
namespace UI {

class TextBox : public Box {
private:
  const wchar_t *content;

public:
  TextBox(uint8_t width, uint8_t height, const wchar_t *content);

  vector<wchar_t *> split_content();
  void show(WINDOW *window, uint16_t x, uint16_t y);
  static TextBox *append(Box *box, float w, float h, const wchar_t *content);
};

} // namespace UI
} // namespace Engine

#endif // TEXT_BOX_HPP
