#include "text_box.hpp"
using namespace Engine::UI;

TextBox::TextBox(uint8_t width, uint8_t height, wchar_t *content)
    : Box(width, height) {
  this->content = content;
}
