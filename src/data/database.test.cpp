/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Stefano Volpe #969766
  04/25/2021

  database.test.cpp: tests for Data::Database and its helper entities.
*/

#include <cassert>

#include "../nostd/test.hpp"
#include "database.hpp"
#include <cstring>

using Data::Database;
using Nostd::it;

#include <iostream>
using namespace std;

int main() {
  it("loads a database from the filesystem", [] {
    Database d("tests/overengineered.conf.csv", "tests/assets",
               "tests/scoreboard.csv");
    // Settings
    const auto &s = d.settings();
    assert(s.size() == 2);
    assert(!s.at(0).label().compare("Sounds"));
    assert(s.at(1).size() == 3);
    // Map chunks
    const auto &m = d.map_chunks();
    assert(m.size() == 11);
    assert(m.at(0).at(19).at(30).value() == Data::MapUnit::nothing);
    assert(m.at(1).at(19).at(30).value() == Data::MapUnit::ground);
    // Sceneries
    const auto &sc = d.sceneries();
    assert(sc.size() == 3);
    assert(sc.at(0).ground.foreground == Engine::Color::grey7);
    assert(sc.at(0).ground.center == u'#');
    assert(sc.at(0).platform.background == Engine::Color::grey7);
    assert(sc.at(0).sky.size() == 3);
    assert(sc.at(0).sky.at(1) == Engine::Color::dodger_blue3);
    // Results
    const auto &r = d.results();
    assert(r.size() == 4);
    assert(r.cbegin()->score() == 8000000);
    assert(r.cend()->name() == "Stefano");
    // Heroes
    const auto &h = d.heroes();
    assert(h.size() == 4);
    assert(h.at(0).name() == "Luca");
    assert(h.at(1).name() == "Andreea");
    assert(h.at(2).name() == "Mattia");
    assert(h.at(3).name() == "Stefano");
    // Enemies
    const auto &e = d.enemies();
    assert(e.size() == 7);
    assert(e.at(0).name() == "boulder");
    assert(e.at(1).name() == "snake");
    // Items
    const auto &i = d.items();
    assert(i.size() == 7);
    assert(i.at(0).name() == "small mushroom");
    assert(i.at(1).name() == "mushroom");
  });
  it("saves user settings on filesystem", [] {
    Database d("tests/overengineered.conf.csv", "tests/assets",
               "tests/scoreboard.csv");
    auto &s = d.settings().at(0);
    s.set(s.begin());
    d.save_settings();
    d = Database("tests/overengineered.conf.csv", "tests/assets",
                 "tests/scoreboard.csv");
    assert(*d.settings().at(0).current_value() == 0);
    auto &s2 = d.settings().at(0);
    s2.set(s2.begin() + 1);
    d.save_settings();
  });
  it("saves user results on filesystem", [] {
    Database d("tests/overengineered.conf.csv", "tests/assets",
               "tests/scoreboard.csv");
    using Data::Pawns::Hero;
    assert(!d.results().empty());
    d.results().push_back(d.results().front());
    d.save_results();
    d = Database("tests/overengineered.conf.csv", "tests/assets",
                 "tests/scoreboard.csv");
    assert(d.results().front().score() == d.results().back().score());
    d.results().pop_back();
    d.save_results();
  });
  it("generates valid audio file paths", [] {
    Database d("tests/overengineered.conf.csv", "tests/assets",
               "tests/scoreboard.csv");
    cout << d.to_audio_filepath("main_menu") << endl;
    assert(strcmp(d.to_audio_filepath("main_menu").c_str(),
                  "tests/assets/sounds/main_menu.wav") == 0);
  });
}
