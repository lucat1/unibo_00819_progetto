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
#include "hero.hpp"
#include "result.hpp"

using Data::Pawns::Result;
using Nostd::it;

int main() {
  it("constructs a Result from scratch", [] {
    Result r{L"Foxy🦊", L'🦊', Engine::Color::aqua, 150};
    assert(!r.name().compare(L"Foxy🦊"));
    assert(r.character() == L'🦊');
    assert(r.foreground() == Engine::Color::aqua);
    assert(r.score() == 150);
  });
  it("constructs a Result from a Hero", [] {
    Result r{Data::Pawns::Hero{
        Engine::Color::aqua, L'🦊', L"Foxy", L"Neat guy.", {}, {}, 5, 10}};
    assert(!r.name().compare(L"Foxy"));
    assert(r.character() == L'🦊');
    assert(r.score() == 0);
    assert(r.foreground() == Engine::Color::aqua);
  });
  it("implicitly converts to int", [] {
    Result r1{L"Foxy🦊", L'🦊', Engine::Color::aqua, 75};
    assert(r1 == 75);
    assert(int{r1} == 75);
    Result r2{L"Andreea", L'✨', Engine::Color::aqua, 150};
    assert(r1 < r2);
  });
}
