/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Stefano Volpe #969766
  06/15/2021

  hero.test.cpp: tests for Data::Pawns::Hero.
*/

#include <cassert>
#include <sstream>

#include "../../engine/colorable.hpp"
#include "../../nostd/test.hpp"
#include "hero.hpp"

using Data::Pawns::Hero;
using Nostd::it;

int main() {
  it("constructs a Hero", [] {
    Hero foxy{Engine::Color::aqua, 'f', "Foxy", "Neat guy.", {}, {}, 5, 10};
    assert(foxy.foreground() == Engine::Color::aqua);
    assert(foxy.character() == 'f');
    assert(foxy.name() == "Foxy");
    assert(foxy.description() == "Neat guy.");
    assert(foxy.current_health() == 5);
    assert(foxy.max_health() == 5);
    assert(!foxy.current_mana());
    assert(foxy.max_mana() == 10);
    assert(!foxy.score());
  });
  it("performs basic health/mana operations", [] {
    Hero foxy{Engine::Color::aqua, 'f', "Foxy", "Neat guy.", {}, {}, 5, 10};
    assert(!foxy.is_dead());
    assert(!foxy.attempt_super_skill());
  });
  it("reads a Hero from a stream", [] {
    Hero foxy{Engine::Color::transparent, u' ', "", "", {}, {}, 1, 1};
    std::istringstream iss{
        "6,f,Foxy,Neat guy.,Tackle,0,0,0,Wait for it,0,0,0,5,10\n"};
    iss >> foxy;
    assert(foxy.foreground() == Engine::Color::teal);
    assert(foxy.character() == 'f');
    assert(foxy.name() == "Foxy");
    assert(foxy.description() == "Neat guy.");
    assert(foxy.current_health() == 5);
    assert(foxy.max_health() == 5);
    assert(!foxy.current_mana());
    assert(foxy.max_mana() == 10);
    assert(!foxy.score());
  });
}
