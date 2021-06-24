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
    Projectile fireball{Engine::Color::red, L'🔥', L"Fireball", 2, 0, 50};
    assert(fireball.foreground() == Engine::Color::red);
    assert(fireball.character() == L'🔥');
    assert(fireball.name() == L"Fireball");
  });
  it("reads a Projectile from a stream", [] {
    Projectile fireball{Engine::Color::transparent, L' ', L"", 0, 0, 0};
    std::wistringstream wiss{L"9,🔥,Fireball,2,0,50\n"};
    wiss >> fireball;
    assert(fireball.foreground() == Engine::Color::red);
    assert(fireball.character() == L'🔥');
    assert(fireball.name() == L"Fireball");
  });
}
