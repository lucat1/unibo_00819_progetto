/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Stefano Volpe #969766
  04/03/2021

  result.test.cpp: tests for Data::Pawns::Result.
*/

#include <cassert>

#include "../../engine/colorable.hpp"
#include "../../nostd/test.hpp"
#include "result.hpp"

using Data::Pawns::Result;
using Nostd::it;

int main() {
  it("constructs a Result", [] {
    Result r(L"Foxy🦊", 150, Engine::Color::aqua, L'🦊');
    assert(!r.name().compare(L"Foxy🦊"));
    assert(r.score() == 150);
    assert(r.foreground() == Engine::Color::aqua);
    assert(r.character() == L'🦊');
  });
  it("implicitly converts to int", [] {
    Result r1(L"Foxy🦊", 75, Engine::Color::aqua, L'🦊');
    assert(r1 == 75);
    assert(int{r1} == 75);
    Result r2(L"Andreea", 150, Engine::Color::aqua, L'✨');
    assert(r1 < r2);
  });
}
