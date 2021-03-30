#include "../nostd/test.hpp"
#include "colorable.hpp"
#include <cassert>
#include <ncurses.h>

using Nostd::it;

int main() {
  it("offers all 0-255 colors", [] {
    short c1 = Engine::color_to_short(Engine::Color::black);
    short cn = Engine::color_to_short(Engine::Color::grey93);
    assert(c1 == 0);
    assert(cn == 255);
  });

  it("prints all the expected colors", [] {
    for (short c = color_to_short(Engine::Color::black);
         c <= color_to_short(Engine::Color::grey93); c++) {
      printf("\x1b[48;5;%dm%3d\e[0m ", c, c);
      if (c == 15 || (c - 15) % 16 == 0)
        std::cout << std::endl;
    }
  });
}
