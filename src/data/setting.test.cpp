/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Stefano Volpe #969766
  04/02/2021

  setting.test.cpp: tests for Data::Setting and its helper entities.
*/

#include <cassert>
#include <sstream>

#include "../nostd/test.hpp"
#include "setting.hpp"

using Data::Setting;
using Nostd::it;

int main() {
  it("constructs a Setting", [] {
    const char label1[]{"Percentage with a step of 10"};
    Setting s1(label1, 0, 11, 10, 5); // 0, 10, ..., 50 (= def = curr), ..., 100
    assert(!s1.label().compare(label1));
    assert(s1.at(0) == 0);
    assert(s1.size() == 11);
    assert(s1.default_value() == s1.begin() + 5);
    assert(s1.current_value() == s1.default_value());
    Setting s2("Switch", 0, 2, 1, 0, 1); // : 0 (= def), 1 (= curr)
    assert(s2.current_value() == s2.begin() + 1);
  });
  it("constructs a Setting with a temporary string",
     [] { assert(Setting("test").label().c_str() != nullptr); });
  it("updates its own current value", [] {
    Setting s("", 0, 11, 10, 5);
    assert(s.set(s.current_value() + 2) == 70);
    assert(s.current_value() == s.begin() + 7);
  });
  it("iterates through possible values", [] {
    Setting s("", 1, 10, 1, 4);
    int check{0};
    for (auto x : s)
      assert(x == ++check);
  });
  it("exposes its first and last values", [] {
    Setting s("", 1, 10, 1, 4);
    assert(s.first() == 1);
    assert(s.last() == 10);
  });
  it("reads from streams", [] {
    std::wstringstream stream("Label,5,10,10,5");
    Setting setting;
    stream >> setting;
    assert(!setting.label().compare("Label"));
    assert(setting.first() == 5);
    assert(setting.size() == 10);
    assert(setting.stride() == 10);
    assert(setting.default_value() == setting.begin() + 5);
    assert(setting.current_value() == setting.begin() + 5);
  });
  it("writes onto streams", [] {
    std::wstringstream stream{};
    stream << Setting("Label", 5, 10, 10, 5);
    assert(!stream.str().compare("Label,5"));
  });
}
