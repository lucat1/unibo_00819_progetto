/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Stefano Volpe #969766
  04/02/2021

  setting.test.cpp: tests for Data::Setting and its helper entities.
*/

#include <cassert>

#include "../nostd/test.hpp"
#include "setting.hpp"

using Data::Setting;
using Nostd::it;

int main() {
  it("constructs a Setting", [] {
    const wchar_t label1[]{L"Percentage with a step of 10"};
    Setting s1(label1, 0, 11, 10, 5); // 0, 10, ..., 50 (= def = curr), ..., 100
    assert(!s1.label().compare(label1));
    assert(s1.at(0) == 0);
    assert(s1.size() == 11);
    assert(s1.default_value() == s1.begin() + 5);
    assert(s1.current_value() == s1.default_value());
    Setting s2(L"Switch", 0, 2, 1, 0, 1); // : 0 (= def), 1 (= curr)
    assert(s2.current_value() == s2.begin() + 1);
  });
  it("updates its own current value", [] {
    Setting s(L"", 0, 11, 10, 5);
    assert(s.set(s.current_value() + 2) == 70);
    assert(s.current_value() == s.begin() + 7);
  });
  it("iterates through possible values", [] {
    Setting s(L"", 1, 10, 1, 4);
    int check{0};
    for (auto x : s)
      assert(x == ++check);
  });
  it("exposes its first and last values", [] {
    Setting s(L"", 1, 10, 1, 4);
    assert(s.first() == 1);
    assert(s.last() == 10);
  });
}
