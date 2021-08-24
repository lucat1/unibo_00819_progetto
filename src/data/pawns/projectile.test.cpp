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
    Projectile fireball{Engine::Color::red, 'f', "Fireball", 2, 0, 50, 5};
    assert(fireball.foreground() == Engine::Color::red);
    assert(fireball.character() == 'f');
    assert(fireball.name() == "Fireball");
  });
  it("constructs a Projectile", [] {
    Projectile fireball{Engine::Color::red, 'f', "Fireball", 2, 0, 50, 5};
    for (int i{5}; i > 0; --i) {
      assert(!fireball.is_expired());
      fireball.count_movement();
    }
    assert(fireball.is_expired());
  });
  it("reads a Projectile from a stream", [] {
    Projectile fireball{Engine::Color::transparent, u' ', "", 0, 0, 0, 0};
    std::istringstream iss{"0,0,9,f,Fireball,2,0,50,5\n"};
    iss >> fireball;
    assert(fireball.foreground() == Engine::Color::red);
    assert(fireball.character() == 'f');
    assert(fireball.name() == "Fireball");
  });
}
