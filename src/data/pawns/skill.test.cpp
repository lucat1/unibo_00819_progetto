/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Stefano Volpe #969766
  06/21/2021

  skill.test.cpp: tests for Data::Pawns::Skill and its helper entities.
*/

#include <cassert>
#include <sstream>

#include "../../nostd/test.hpp"
#include "skill.hpp"

using Data::Pawns::Skill;
using Nostd::it;

int main() {
  it("reads a Skill from a stream", [] {
    Skill fireMagic{};
    std::istringstream iss{"1,1,0,9,f,Fireball,2,0,50,5,0,0\n"};
    iss >> fireMagic;
    assert(fireMagic.projectiles().size() == 1);
  });
}
