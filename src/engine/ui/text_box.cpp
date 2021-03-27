#include "text_box.hpp"

Engine::UI::TextBox::TextBox(uint16_t max_width, uint16_t max_height,
                             const wchar_t *content)
    : Box(max_width, max_height) {
  this->content = content;
  split_content();
}
Engine::UI::TextBox::TextBox(uint16_t max_width, uint16_t max_height,
                             Nostd::WString &&content)
    : Box(max_width, max_height) {
  this->content = content;
  split_content();
}

// splits the content into various lines to fit into `max_width` and adds
// '-' where necessary, when splitting a word
void Engine::UI::TextBox::split_content() {
  lines.clear();
  size_t len = content.length();
  while (len > max_width) {
    size_t ll = len < max_width ? Nostd::WString::npos : max_width - 1;

    Nostd::WString sub = content.substr(content.length() - len, ll + 1).ltrim();
    if (!Nostd::iswspace(sub[ll]) && ll != Nostd::WString::npos) {
      // when we have two ending chars that are not whitespace we consider this
      // as a word and we add the - charter. Otherwhise we consider this the
      // beginning of a new word and leave it for the next line.
      if (!Nostd::iswspace(sub[ll - 1]))
        sub.back() = L'-';
      else {
        ll--; // leave the new word in the next line
        sub.back() = L' ';
      }
    }

    lines.push_back(sub);
    len -= ll;
  }
  lines.push_back(
      content.substr(content.length() - len, Nostd::WString::npos).ltrim());
}

void Engine::UI::TextBox::show(WINDOW *window, uint16_t x, uint16_t y) {
  start_color(window);

  for (size_t i = 0; i < lines.size(); i++) {
    auto line = lines[i];
    mvwaddwstr(window, y + i, x + (fr ? max_width - line.length() : 0),
               line.c_str());
  }

  end_color(window);
}

Nostd::Pair<uint16_t, uint16_t> Engine::UI::TextBox::size() {
  uint16_t height = (uint16_t)lines.size();
  uint16_t width = lines.size() > 0 ? lines.at(0).length() : 0;
  return {width, height};
}
