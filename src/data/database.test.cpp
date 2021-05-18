/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Stefano Volpe #969766
  04/25/2021

  database.test.cpp: tests for Nostd::Database and its helper entities.
*/

#include <cassert>

#include "../nostd/test.hpp"
#include "database.hpp"

using Data::Database;
using Nostd::it;

int main() {
  it("loads a database from the filesystem", [] {
    Database d("tests/alma.conf.csv", "tests/assets/", "tests/scoreboard.csv");
    // Settings
    const auto &s = d.settings();
    assert(s.size() == 2);
    assert(!s.at(0).label().compare(L"Sounds"));
    assert(s.at(1).size() == 3);
    // Map chunks
    const auto &m = d.map_chunks();
    assert(m.size() == 2);
    assert(m.at(0).ending_row() == 16);
    assert(m.at(0).at(19).at(30).value() == Data::MapUnit::ground);
    assert(m.at(1).starting_row() == 17);
    assert(m.at(1).at(5).at(69).value() == Data::MapUnit::item);
    // Sceneries
    const auto &sc = d.sceneries();
    assert(sc.size() == 1);
    assert(sc.at(0).ground.foreground == Engine::Color::red);
    assert(sc.at(0).ground.center == L'#');
    assert(sc.at(0).platform.background == Engine::Color::maroon);
    assert(sc.at(0).sky.size() == 2);
    assert(sc.at(0).sky.at(1) == Engine::Color::blue3_1);
    // Results
    const auto &r = d.results();
    assert(r.size() == 4);
    assert(r.cbegin()->score() == 8000000);
    assert(r.cend()->nickname() == L"Stefano");
  });
  it("saves user settings on filesystem", [] {
    Database d("tests/alma.conf.csv", "tests/assets/", "tests/scoreboard.csv");
    auto &s = d.settings().at(0);
    s.set(s.begin());
    d.save_settings();
    d = Database("tests/alma.conf.csv", "tests/assets/",
                 "tests/scoreboard.csv");
    assert(*d.settings().at(0).current_value() == 0);
    auto &s2 = d.settings().at(0);
    s2.set(s2.begin() + 1);
    d.save_settings();
  });
  it("saves user results on filesystem", [] {
    Database d("tests/alma.conf.csv", "tests/assets/", "tests/scoreboard.csv");
    using Data::Interactables::Hero;
    assert(!d.results().empty());
    d.results().push_back(d.results().front());
    d.save_results();
    d = Database("tests/alma.conf.csv", "tests/assets/",
                 "tests/scoreboard.csv");
    assert(d.results().front().score() == d.results().back().score());
    d.results().pop_back();
    d.save_results();
  });
}
