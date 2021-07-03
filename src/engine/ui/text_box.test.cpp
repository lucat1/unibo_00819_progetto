/*
  University of bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Luca Tagliavini #971133
  03/15/2021

  text_box.test..cpp: Tests for TextBox::split_content
*/

#include "text_box.hpp"
#include "../../nostd/test.hpp"
#include <cassert>

using Engine::UI::TextBox;
using Nostd::it;

int main() {
  TextBox t = TextBox("");
  it("doesn't split a small enough line", [t] {
    Nostd::WString str = "this is a test line";
    auto lines = t.split_content(str, 100);
    assert(lines.size() == 1);
    assert(lines[0].compare(str) == 0);
  });

  it("splits the line when there's a whitespace", [t] {
    Nostd::WString str = "this is a test line";
    auto lines = t.split_content(str, 10);
    assert(lines.size() == 2);
    assert(lines[0].compare("this is a ") == 0);
  });

  it("splits the line across a word", [t] {
    Nostd::WString str = "this is a test line";
    auto lines = t.split_content(str, 12);
    assert(lines.size() == 2);
    assert(lines[0].compare("this is a te-") == 0);
    assert(lines[1].compare("st line") == 0);
  });
}
