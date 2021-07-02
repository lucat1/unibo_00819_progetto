/*
  University of bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Luca Tagliavini #971133
  03/15/2021

  text_box.cpp: Implements the Engine::UI::TextBox class with the line-splitting
  algoritm to make a given strign fit inside a max_width large boh. Liens are
  cut, with trailing '-' added where necessary.
*/

#include "text_box.hpp"
#include <algorithm>

Engine::UI::TextBox::TextBox(const wchar_t *content) : Box() {
  this->content = content;
}
Engine::UI::TextBox::TextBox(const Nostd::WString &content)
    : TextBox(content.c_str()) {}

void Engine::UI::TextBox::update_lines(szu max_width) {
  if (max_width != old_max_width)
    lines = split_content(content, max_width);
  old_max_width = max_width;
}

Engine::UI::TextBox::strings
Engine::UI::TextBox::split_content(const Nostd::WString content,
                                   szu max_width) {
  strings lines;
  if (max_width == 0)
    return lines;

  size_t len = content.length(), start = 0;
  while (len > max_width) {
    size_t wrote = std::min(len - start, (size_t)max_width);
    auto sub = content.substr(start, wrote);
    if (!Nostd::iswspace(sub[wrote - 1])) {
      // when we have two ending chars that are not whitespace we consider this
      // as a word and we add the - charter. Otherwhise we consider this the
      // beginning of a new word and leave it for the next line.
      if (!Nostd::iswspace(sub[wrote - 2]))
        sub.back() = L'-';
      else {
        wrote--; // leave the new word in the next line
        sub.back() = L' ';
      }
    }

    lines.push_back(content.substr(start, wrote));
    start += wrote;
    len -= wrote;
  }

  // append remaining if we have any
  if (start != len - 1)
    lines.push_back(content.substr(start));
  return lines;
}

void Engine::UI::TextBox::show(WINDOW *window, szu x, szu y, szu max_width,
                               szu max_height) {
  update_lines(max_width);
  start_color(window);

  // max_height is respected, maybe we could add trialing dots as a proper
  // termination to the string. Right now it's quite rough but respecitng the
  // size is the first priority.
  for (size_t i = 0; i < std::min(max_height, (szu)lines.size()); i++) {
    auto line = lines[i];
    mvwaddwstr(window, y + i, x + (fr ? max_width - line.length() : 0),
               line.c_str());
  }

  end_color(window);
  wnoutrefresh(window);
}

Engine::UI::Box::dim Engine::UI::TextBox::size(szu max_width, szu max_height) {
  update_lines(max_width);
  szu height = std::min((szu)lines.size(), max_height);
  szu width = fr ? max_width
                 : std::min((szu)(lines.size() > 0 ? lines.at(0).length() : 0),
                            max_width);
  return {width, height};
}
