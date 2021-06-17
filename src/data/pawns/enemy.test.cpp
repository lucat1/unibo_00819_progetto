/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Stefano Volpe #969766
  06/17/2021

  enemy.test.cpp: tests for Data::Pawns::Enemy and its helper entities.
*/

#include <cassert>
#include <sstream>

#include "../../engine/colorable.hpp"
#include "../../nostd/test.hpp"
#include "enemy.hpp"

using Data::Pawns::Enemy;
using Nostd::it;

int main() {
  it("constructs an Enemy", [] {
    Enemy goomba{Engine::Color::maroon, L'🍄', L"Goomba", {}, 1, 0, 50, 1};
    assert(goomba.foreground() == Engine::Color::maroon);
    assert(goomba.character() == L'🍄');
    assert(goomba.name() == L"Goomba");
  });
  it("checks an Enemy's behavior", [] {
    Enemy goomba{Engine::Color::maroon, L'🍄', L"Goomba", {}, 1, 0, 50, 1};
    assert(goomba.has_behavior(Enemy::Behavior::moving));
    assert(!goomba.has_behavior(Enemy::Behavior::flying));
  });
  it("reads a Hero from a stream", [] {
    Enemy goomba{Engine::Color::transparent, L' ', L"", {}, 0, 0, 0, 1};
    std::wistringstream wiss{L"1,🍄,Goomba,,1,0,50,1\n"};
    wiss >> goomba;
    assert(goomba.foreground() == Engine::Color::maroon);
    assert(goomba.character() == L'🍄');
    assert(goomba.name() == L"Goomba");
    assert(goomba.has_behavior(Enemy::Behavior::moving));
    assert(!goomba.has_behavior(Enemy::Behavior::flying));
  });
}
