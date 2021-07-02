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
    std::wistringstream wiss{L"1,1,0,9,🔥,Fireball,2,0,50,5,0,0\n"};
    wiss >> fireMagic;
    assert(fireMagic.projectiles().size() == 1);
  });
}
