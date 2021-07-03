/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Stefano Volpe #969766
  06/19/2021

  projectile.test.cpp: tests for Data::Pawns::Projectile and its helper
  entities.
*/

#include <cassert>
#include <sstream>

#include "../../engine/colorable.hpp"
#include "../../nostd/test.hpp"
#include "projectile.hpp"

using Data::Pawns::Projectile;
using Nostd::it;

int main() {
  it("constructs a Projectile", [] {
    Projectile fireball{Engine::Color::red, u'🔥', "Fireball", 2, 0, 50, 5};
    assert(fireball.foreground() == Engine::Color::red);
    assert(fireball.character() == u'🔥');
    assert(fireball.name() == "Fireball");
  });
  it("constructs a Projectile", [] {
    Projectile fireball{Engine::Color::red, u'🔥', "Fireball", 2, 0, 50, 5};
    for (int i{5}; i > 0; --i) {
      assert(!fireball.isExpired());
      fireball.countMovement();
    }
    assert(fireball.isExpired());
  });
  it("reads a Projectile from a stream", [] {
    Projectile fireball{Engine::Color::transparent, u' ', "", 0, 0, 0, 0};
    std::wistringstream wiss{"9,🔥,Fireball,2,0,50,5\n"};
    wiss >> fireball;
    assert(fireball.foreground() == Engine::Color::red);
    assert(fireball.character() == u'🔥');
    assert(fireball.name() == "Fireball");
  });
}
