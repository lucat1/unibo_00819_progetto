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

Engine::UI::TextBox::TextBox(const char *content) : Box() {
  this->content = content;
}
Engine::UI::TextBox::TextBox(const Nostd::String &content)
    : TextBox(content.c_str()) {}

void Engine::UI::TextBox::update_lines(szu max_width) {
  if (max_width != old_max_width)
    lines = split_content(content, max_width);
  old_max_width = max_width;
}

Engine::UI::TextBox::strings
Engine::UI::TextBox::split_content(const Nostd::String content, szu max_width) {
  strings lines;
  if (max_width == 0)
    return lines;

  size_t pos = 0;
  while (content.length() - pos > max_width) {
    size_t wrote = std::min(content.length() - pos, (size_t)max_width);
    auto sub = content.substr(pos, wrote);
    if (Nostd::iswspace(content[pos + wrote])) {
      // if we cut right at the end of a word (aka just before a whitespace)
      // ditch that whitespace so the new line doesn't start with a blank char
      wrote++;
    } else if (!Nostd::iswspace(sub[wrote - 1])) {
      // when we have two ending chars that are not whitespace we consider this
      // as a word and we add the - charter. Otherwhise we consider this the
      // beginning of a new word and leave it for the next line.
      if (!Nostd::iswspace(sub[wrote - 2]))
        sub.back() = u'-';
      else
        sub = sub.substr(0, wrote - 1);
      wrote--; // leave the new word in the next line
    }

    lines.push_back(sub);
    pos += wrote;
  }

  // append remaining if we have any
  if (pos != content.length() - 1)
    lines.push_back(content.substr(pos));
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
    mvwaddstr(window, y + i, x + (fr ? max_width - line.length() : 0),
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
