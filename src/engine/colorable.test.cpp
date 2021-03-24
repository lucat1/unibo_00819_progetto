#include "../util/test.hpp"
#include "colorable.hpp"
#include <assert.h>
#include <ncurses.h>

int main() {
  it("offers all 0-255 colors", {
<<<<<<< HEAD
    int c1 = Engine::color_to_int(Engine::Color::black);
    int cn = Engine::color_to_int(Engine::Color::grey93);
=======
    short c1 = Engine::color_to_short(Engine::Color::black);
    short cn = Engine::color_to_short(Engine::Color::grey93);
>>>>>>> 2e9becb (add coloring support to TextBoxes)
    assert(c1 == 0);
    assert(cn == 255);
  });

  it("prints all the expected colors", {
<<<<<<< HEAD
    for (int c = color_to_int(Engine::Color::black);
         c <= color_to_int(Engine::Color::grey93); c++) {
=======
    for (short c = color_to_short(Engine::Color::black);
         c <= color_to_short(Engine::Color::grey93); c++) {
>>>>>>> 2e9becb (add coloring support to TextBoxes)
      printf("\x1b[48;5;%dm%3d\e[0m ", c, c);
      if (c == 15 || (c - 15) % 16 == 0)
        std::cout << std::endl;
    }
  });
}
