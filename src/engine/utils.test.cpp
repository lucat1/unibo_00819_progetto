/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Luca Tagliavini #971133
  04/27/2021

  utils.test.cpp: Unit tests for Engine::*'s utilities
*/

#include "utils.hpp"
#include "../nostd/test.hpp"
#include "../nostd/wstring.hpp"
#include <cassert>

using Engine::Utils::leftpad;
using Nostd::it;
using Nostd::WString;

int main() {
  it("generates a padded string of the correct length", [] {
    WString str1 = L"yet another test string", str2 = L"test test test string";
    leftpad(100, str1);
    assert(str1.length() == 100);
  });
}
