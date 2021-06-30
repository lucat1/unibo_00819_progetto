#include "engine/menu/main.hpp"
#include "data/mugshot.hpp"
#include "data/pawns/hero.hpp"
#include "engine/colorable.hpp"
#include "engine/menu/results.hpp"
#include "engine/menu/settings.hpp"
#include "engine/screen.hpp"
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
  Screen screen;
  handle(screen.open());
  screen.set_content<Menu::Main>();
  Nostd::Vector<Data::Setting> settings;
  settings.push_back(Data::Setting(L"Sound", 0, 2, 1, 0, 1));
  settings.push_back(Data::Setting(L"Frames Per Second", 30, 3, 30, 1));

  // TODO: properly by calling database.results()
  Nostd::List<Data::Pawns::Result> results;
  results.push_back(Data::Pawns::Result(L"Lienin", 100293, Color::red, L'='));
  results.push_back(Data::Pawns::Result(L"Adolf", 98666, Color::yellow, L'/'));
  results.push_back(Data::Pawns::Result(L"Benito", 20034, Color::green, L'!'));

  int key;
  bool running = true;
  while (running) {
    // quit if usleep is blocked by an interrupt and the key is an ERR
    if (usleep(1000000 / 25) == EINTR) // 25fps
      running = false;

    if (screen.get_content()->is_over()) {
      if (screen.is_content<Menu::Main>()) {
        // do something when the main menu is exited
        auto res = screen.get_content<Menu::Main>()->get_result();
        switch (res) {
        case Menu::Main::Result::quit:
          running = false;
          break;
        case Menu::Main::Result::settings:
          screen.set_content<Menu::Settings,
                             const Nostd::Vector<Data::Setting> &>(settings);
          break;
        case Menu::Main::Result::play:
          // TODO: change me
          screen.set_content<Menu::Results,
                             const Nostd::List<Data::Pawns::Result> &>(results);
          break;
        default:
          break;
        }
      } else {
        if (screen.is_content<Menu::Settings>())
          settings = screen.get_content<Menu::Settings>()->get_result();

        // always go back to the main menu after some menus close
        screen.set_content<Menu::Main>();
      }
    }

    // keyboard handling
    key = getch();
    switch (key) {
    case KEY_RESIZE:
      handle(screen.reposition());
      break;

    case '\n':
    case KEY_ENTER: // enter key for the numpad
      screen.send_event(Drawable::Event::interact);
      break;

    case 'k':
    case KEY_UP:
      screen.send_event(Drawable::Event::move_up);
      break;

    case 'j':
    case KEY_DOWN:
      screen.send_event(Drawable::Event::move_down);
      break;

    case 'h':
    case KEY_LEFT:
      screen.send_event(Drawable::Event::move_left);
      break;

    case 'l':
    case KEY_RIGHT:
      screen.send_event(Drawable::Event::move_right);
      break;
    case ERR:
      // ignore ncurses's getch errors
      break;
    };
  }

  // Sample Hero
  Data::Pawns::Hero leo{
      Engine::Color::red, L'🦁', L"Leo", L"Neat guy.", {}, {}, 9, 4};
  wifstream wifs{"tests/assets/img/heroes.txt"};
  wifs.ignore();
  wifs.ignore();
  wifs >> leo.mugshot();
  for (auto &row : leo.mugshot()) {
    for (auto &cell : row)
      std::wcerr << cell.value()->character();
    std::wcerr << L'\n';
  }
  wifs.close();
  return 0;
}
