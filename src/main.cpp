#include "engine/menu/main.hpp"
#include "data/database.hpp"
#include "engine/audio.hpp"
#include "engine/colorable.hpp"
#include "engine/menu/select.hpp"
#include "engine/menu/settings.hpp"
#include "engine/scene/scene.hpp"
#include "engine/screen.hpp"
#include "world/world.hpp"
#include <fstream>
#include <iostream>
#include <unistd.h>
using namespace std;
using namespace Engine;

void handle(bool can_display) {
  if (can_display)
    return;

  cout << "Error while opening screen" << endl;
  exit(1);
}

int main() {
  Audio::fetch_tool();
  if (Audio::play("tests/assets/sound/main_menu.wav")) {
    cout << "started playing" << endl;
  }
  int i = 0;
  while (i < 5) {
    sleep(1);
    cout << "still running: "
         << (Audio::status() == Audio::PlayerState::playing ? "p" : "s")
         << endl;
    i++;
  }
  Audio::stop();
  return 0;
}
