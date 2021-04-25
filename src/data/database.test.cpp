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
    assert(d.settings().size() == 2);
    assert(d.map_chunks().size() == 2);
    assert(d.sceneries().size() == 1);
    assert(d.results().size() == 4);
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
}
