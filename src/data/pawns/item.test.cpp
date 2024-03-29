/*
 University of Bologna
 First cicle degree in Computer Science
 00819 - Programmazione

 Stefano Volpe #969766
 06/17/2021

 item.test.cpp: tests for Data::Pawns::Item.
*/

#include <cassert>
#include <sstream>

#include "../../engine/colorable.hpp"
#include "../../nostd/test.hpp"
#include "item.hpp"

using Data::Pawns::Item;
using Nostd::it;

int main() {
  it("constructs an Item", [] {
    Item mushroom{Engine::Color::red, 'm', "Mushroom", 2, false, 0, false, 50};
    assert(mushroom.foreground() == Engine::Color::red);
    assert(mushroom.character() == 'm');
    assert(mushroom.name() == "Mushroom");
  });
  it("reads an Item from a stream", [] {
    Item mushroom{Engine::Color::transparent, u' ', "", 0, false, 0, false, 0};
    std::istringstream iss{"9,m,Mushroom,2,0,0,0,50\n"};
    iss >> mushroom;
    assert(mushroom.foreground() == Engine::Color::red);
    assert(mushroom.character() == 'm');
    assert(mushroom.name() == "Mushroom");
  });
}
