#include "text_box.hpp"
#include <cstring>
#include <unistd.h>
#include <vector>
using namespace std;
using namespace Engine::UI;

TextBox::TextBox(uint8_t width, uint8_t height, wchar_t *content)
    : Box(width, height) {
  this->content = content;
}

// splits a string by a given token
// FIXME: luca del futuro, pulire please
vector<wchar_t *> strsplit(wchar_t *str, wchar_t token) {
  vector<wchar_t *> result;
  size_t i = 0, start = 0, len = 0;
  bool in_word = false;

  while (str[i] != '\0') {
    if (!in_word) {
      if (str[i] != ' ') {
        in_word = true;
        start = i;
        len = 0;
      }
    } else {
      if (str[i] == ' ') {
        in_word = false;
        if (len != 0) {
          wchar_t *cpy;
          wcsncpy(cpy, str + start, len);
          result.push_back(cpy);
        }
      } else
        len = len + 1;
    }
    i = i + 1;
  }

  return result;
}

// split_content splits the content of the TextBox in various lines to fit the
// given width
// FIXME: cambiare. Con questo approccio eliminiamo gli spazi multipli
// consecutivi dividendo in parole. Si semplifica la vita ma non riproduce
// fedelmente il contenuto.
vector<wchar_t *> TextBox::split_content() {
  vector<wchar_t *> words = strsplit(this->content, ' ');
  words.push_back((wchar_t *)"sono una stringa di prova");
  /* for (int i = 0; i < words.size(); i++) { */

  /* } */
  return words;
}

void TextBox::show(uint16_t x, uint16_t y) {
  vector<wchar_t *> lines = this->split_content();
  for (vector<wchar_t *>::size_type i = 0; i < lines.size(); i++) {
    // posiziona cursore, scrivi linea
    mvwaddwstr(this->window, y + i, x, lines.at(i));
    // nuova linea
  }
}
