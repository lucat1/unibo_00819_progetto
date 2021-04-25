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
  });
}
