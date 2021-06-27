/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Luca Tagliavini #971133
  04/10/2021

  center.test.cpp: A few unit tests to check the functionality of the
  Engine::UI::Center class
*/

#include "center.hpp"
#include "../../nostd/test.hpp"
#include <cassert>

using Engine::UI::Box;
using Engine::UI::Center;
using Nostd::it;
using namespace Engine::UI;

Box::szu x = -1, y = -1, w = -1, h = -1;

class TestBox : public Box {
public:
  static constexpr const szu width = 10, height = 10;
  void show(WINDOW *window, szu _x, szu _y, szu _w, szu _h) {
    x = _x;
    y = _y;
    w = _w;
    h = _h;
  }
  dim size(szu max_width, szu max_height) { return {width, height}; }
};

int main() {
  it("reports the appropriate width and height", [] {
    auto center = new Center(); // vertical centering
    Box::dim expected = {0, 100};
    assert(center->size(100, 100) == expected);

    center->propb(Box::Property::center_horizontal, true);
    expected = {100, 0};
    assert(center->size(100, 100) == expected);
  });

  it("positions one child centered vertically", [] {
    auto center = new Center();
    center->append<TestBox>();
    center->show(nullptr, 0, 0, 100, 100);
    assert(w == TestBox::width);
    assert(h == TestBox::height);
    assert(x == 0);
    assert(y == (100 - TestBox::height) / 2);
  });

  it("positions multiple children centered vertically", [] {
    auto center = new Center();
    center->append<TestBox>();
    center->append<TestBox>();
    center->append<TestBox>();
    center->show(nullptr, 0, 0, 100, 100);
    assert(w == TestBox::width);
    assert(h == TestBox::height);
    assert(x == 0);
    assert(y == (100 - 3 * TestBox::height) / 2 + (2 * TestBox::height));
  });

  it("positions one child centered horizontally", [] {
    auto center = new Center();
    center->propb(Box::Property::center_horizontal, true);
    center->append<TestBox>();
    center->show(nullptr, 0, 0, 100, 100);
    assert(w == TestBox::width);
    assert(h == TestBox::height);
    assert(x == (100 - TestBox::width) / 2);
    assert(y == 0);
  });

  it("nested centering works with one child", [] {
    auto root = new Center();
    root->propb(Box::Property::center_horizontal, true);
    auto center = root->append<Center>();
    center->append<TestBox>();
    root->show(nullptr, 0, 0, 100, 100);

    assert(w == TestBox::width);
    assert(h == TestBox::height);
    assert(x == (100 - TestBox::width) / 2);
    assert(y == (100 - TestBox::height) / 2);
  });

  it("nested centering works with multiple childen", [] {
    auto root = new Center();
    root->propb(Box::Property::center_horizontal, true);
    auto center = root->append<Center>();
    center->append<TestBox>();
    center->append<TestBox>();
    center->append<TestBox>();
    root->show(nullptr, 0, 0, 100, 100);

    assert(w == TestBox::width);
    assert(h == TestBox::height);
    assert(x == (100 - TestBox::width) / 2);
    assert(y == (100 - 3 * TestBox::height) / 2 + (2 * TestBox::height));
  });
}
