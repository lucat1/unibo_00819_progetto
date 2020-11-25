#include "engine/screen.hpp"
#include <iostream>
using namespace std;

int main() {
  Engine::Screen screen;

  if (screen.open()) {
    cout << "Error while opening screen" << endl;
    return 1;
  }

  while (getch() != 'q')
    ;

  screen.close();
  return 0;
}
