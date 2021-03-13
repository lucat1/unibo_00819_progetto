#include "text_box.hpp"
#include <algorithm>
#include <cstring>
#include <cwchar>
#include <iostream>
#include <iostream> // TODO: remove
#include <vector>
using namespace std;
using namespace Engine::UI;

// TextBox straigh up ignores the height value as it is defined by its width and
// content length.
// NOTE(tip): you can wrap a TextBox in a Box with an aribtrary height if you
// for some reason wanna fill some amount of height
TextBox::TextBox(uint8_t max_width, uint8_t max_height, const wchar_t *content)
    : Box(max_width, max_height) {
  this->content = content;
  std::cout << max_width << std::endl;
  std::cout << this->max_width << std::endl;
  std::cout << max_height << std::endl;
  std::cout << this->max_height << std::endl;
  this->lines = split_content();
  std::cout << this->max_width << std::endl;
  std::cout << this->max_height << std::endl;
}

wchar_t *emptystr(size_t len) {
  wchar_t *res = new wchar_t[len];
  for (size_t i = 0; i < len; i++)
    res[i] = '\0';
  return res;
}

// split_content splits the content of the TextBox in various lines to fit the
// given width
vector<wchar_t *> TextBox::split_content() {
  vector<wchar_t *> lines;
  vector<wchar_t *>::size_type line_i = 0;
  size_t i = 0, line_len = 0;
  lines.push_back(emptystr(max_width + 1)); // the initial line

  while (content[i] != '\0') {
    wchar_t *line = lines.at(line_i);
    if (line_len < max_width) {
      // we are within the given width so we can safely add the char to the
      // current line
      line[line_len] = content[i];
      line_len++;
    } else {
      wchar_t *new_line = emptystr(max_width + 1);
      wchar_t c = line[line_len - 1];
      // add a - if we're splitting a word (NOT a whitespace)
      // and copy the trimmed char into the new line
      if (c != ' ') {
        line[line_len - 1] = '-';
        new_line[0] = c;
        line_len = 1;
      } else
        line_len = 0;

      if (content[i] != ' ' || line_len != 0)
        new_line[line_len] = content[i];

      lines.push_back(new_line);
      line_len = wcslen(new_line);
      line_i++;
    }
    i = i + 1;
  }

  return lines;
}

void TextBox::show(WINDOW *window, uint16_t x, uint16_t y) {
  for (vector<wchar_t *>::size_type i = 0; i < lines.size(); i++) {
    wchar_t *line = lines.at(i);
    mvwaddwstr(window, y + i, x, line);
    delete line;
  }
  lines.clear();
}

bsize_t TextBox::size() {
  uint16_t height = (uint16_t)lines.size();
  std::cout << max_width << " " << height << std::endl;
  return bsize_t{{max_width, height}};
}
