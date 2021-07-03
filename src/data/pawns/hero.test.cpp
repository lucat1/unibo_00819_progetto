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
    Hero foxy{
        Engine::Color::aqua, u'🦊', "Foxy", "Neat guy.", {}, {}, 5, 10};
    assert(foxy.foreground() == Engine::Color::aqua);
    assert(foxy.character() == u'🦊');
    assert(foxy.name() == "Foxy");
    assert(foxy.description() == "Neat guy.");
    assert(foxy.currentHealth() == 5);
    assert(foxy.maxHealth() == 5);
    assert(!foxy.currentMana());
    assert(foxy.maxMana() == 10);
    assert(!foxy.score());
  });
  it("performs basic health/mana operations", [] {
    Hero foxy{
        Engine::Color::aqua, u'🦊', "Foxy", "Neat guy.", {}, {}, 5, 10};
    assert(!foxy.isDead());
    assert(!foxy.attemptSuperSkill());
  });
  it("reads a Hero from a stream", [] {
    Hero foxy{Engine::Color::transparent, u' ', "", "", {}, {}, 1, 1};
    std::wistringstream wiss{"6,🦊,Foxy,Neat guy.,0,0,0,0,0,0,5,10\n"};
    wiss >> foxy;
    assert(foxy.foreground() == Engine::Color::teal);
    assert(foxy.character() == u'🦊');
    assert(foxy.name() == "Foxy");
    assert(foxy.description() == "Neat guy.");
    assert(foxy.currentHealth() == 5);
    assert(foxy.maxHealth() == 5);
    assert(!foxy.currentMana());
    assert(foxy.maxMana() == 10);
    assert(!foxy.score());
  });
}
