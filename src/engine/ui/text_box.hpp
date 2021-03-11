#ifndef TEXT_BOX_HPP
#define TEXT_BOX_HPP

#include "box.hpp"

namespace Engine {
namespace UI {

class TextBox : public Box {
public:
  wchar_t *content;
  static TextBox append(Box box);
  TextBox(uint8_t width, uint8_t height, wchar_t *content);
};

} // namespace UI
} // namespace Engine

#endif // TEXT_BOX_HPP
