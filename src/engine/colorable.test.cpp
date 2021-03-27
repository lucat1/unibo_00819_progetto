#include "../util/test.hpp"
#include "colorable.hpp"
#include <assert.h>
#include <ncurses.h>

int main() {
  it("offers all 0-255 colors", {
    int c1 = Engine::color_to_int(Engine::Color::black);
    int cn = Engine::color_to_int(Engine::Color::grey93);
    assert(c1 == 0);
    assert(cn == 255);
  });

  it("prints all the expected colors", {
    for (int c = color_to_int(Engine::Color::black);
         c <= color_to_int(Engine::Color::grey93); c++) {
      printf("\x1b[48;5;%dm%3d\e[0m ", c, c);
      if (c == 15 || (c - 15) % 16 == 0)
        std::cout << std::endl;
    }
  });
}
