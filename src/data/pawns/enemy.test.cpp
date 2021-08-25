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
    Enemy goomba{Engine::Color::maroon, 'm', "Goomba", {}, 1, 0, 50, 1};
    assert(goomba.foreground() == Engine::Color::maroon);
    assert(goomba.character() == 'm');
    assert(goomba.name() == "Goomba");
  });
  it("checks an Enemy's behavior", [] {
    Enemy goomba{Engine::Color::maroon, 'm', "Goomba", {}, 1, 0, 50, 1};
    assert(goomba.has_behavior(Enemy::Behavior::walking));
    assert(!goomba.has_behavior(Enemy::Behavior::horizontal_flying));
  });
  it("reads an Enemy from a stream", [] {
    Enemy goomba{Engine::Color::transparent, u' ', "", {}, 0, 0, 0, 1};
    std::istringstream iss{"1,m,Goomba,Tackle,0,0,0,1,0,50,1\n"};
    iss >> goomba;
    assert(goomba.foreground() == Engine::Color::maroon);
    assert(goomba.character() == 'm');
    assert(goomba.name() == "Goomba");
    assert(goomba.has_behavior(Enemy::Behavior::walking));
    assert(!goomba.has_behavior(Enemy::Behavior::horizontal_flying));
  });
}
