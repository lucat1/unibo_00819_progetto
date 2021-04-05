/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Stefano Volpe #969766
  04/03/2021

  result.test.cpp: tests for Data::Result.
*/

#include <cassert>

#include "../nostd/test.hpp"
#include "result.hpp"

using Data::Result;
using Nostd::it;

int main() {
  it("constructs a Result", [] {
    Result r(L"Foxy🦊", nullptr, 150);
    assert(!r.nickname().compare(L"Foxy🦊"));
    assert(!r.hero());
    assert(r.score() == 150);
  });
  it("implicitly converts to int", [] {
    Result r1(L"FoxySeta", nullptr, 75);
    assert(r1 == 75);
    assert(int{r1} == 75);
    Result r2(L"Foxy🦊", nullptr, 150);
    assert(r1 < r2);
  });
}
