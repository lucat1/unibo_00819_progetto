#ifndef TEXT_BOX_HPP
#define TEXT_BOX_HPP

#include "../../nostd/wstring.hpp"
#include "box.hpp"
#include <ncurses.h>

namespace Engine {
namespace UI {

// TextBox straigh up ignores the height value as it is defined by its width and
// content length.
// NOTE(tip): you can wrap a TextBox in a Box with an aribtrary height if you
// for some reason wanna fill some amount of height
class TextBox : public Box {
public:
  Nostd::WString content;
  Nostd::Vector<Nostd::WString> lines;

  static constexpr const wchar_t *append_default_value = L"";
  TextBox(uint16_t max_width, uint16_t max_height,
          std::map<enum Box::Props, uint16_t> props = {},
          Nostd::WString &&content = L"");
  TextBox(uint16_t max_width, uint16_t max_height,
          std::map<enum Box::Props, uint16_t> props = {},
          const wchar_t *content = L"");

  void split_content();
  Nostd::Pair<uint16_t, uint16_t> size();
  void show(WINDOW *window, uint16_t x, uint16_t y);
};

} // namespace UI
} // namespace Engine

#endif // TEXT_BOX_HPP
