/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Luca Tagliavini #971133
  03/13/2021

  box.test.cpp: Various unit tests to check the functionality of the
  Engine::UI::Box class
*/

#include "box.hpp"
#include "../../nostd/test.hpp"
#include "text_box.hpp"
#include <algorithm>
#include <cassert>

using Engine::UI::Box;
using Engine::UI::TextBox;
using Nostd::it;

int main() {
  Box *box = new Box();
  it("constructs a box properly", [box] {
    assert(box->get_first_child() == nullptr);
    assert(box->get_last_child() == nullptr);
    assert(box->get_sibling() == nullptr);
    assert(box->get_parent() == nullptr);
  });

  auto child = box->append<Box>();
  it("adds a new child", [box, child] {
    assert(box->get_sibling() == nullptr);
    assert(box->get_first_child() == child);
    assert(box->get_last_child() == child);
    assert(child->get_parent() == box);

    assert(child->get_sibling() == nullptr);
    assert(child->get_first_child() == nullptr);
    assert(child->get_last_child() == nullptr);
  });

  it("properly returns the first child", [] {
    Box *box = new Box();
    auto child = box->append<Box>();
    auto child1 = box->child(0);
    assert(child1 != nullptr);
    assert(child == child1);
  });

  auto snd_child = box->append<Box>();
  it("adds a second child", [box, child, snd_child] {
    assert(box->get_first_child() == child);
    assert(box->get_last_child() == snd_child);
    assert(snd_child->get_parent() == box);
    assert(child->get_sibling() == snd_child);
    assert(snd_child->get_sibling() == nullptr);
  });

  Box *box1 = new Box();
  it("reports the correct size when empty", [box1] {
    auto size = box1->size(1000, 1000);
    assert(size.first == 0);
    assert(size.second == 0);
  });

  TextBox *tb1 = box1->append<TextBox, const char *>("this is a test text");
  it("reports the correct size when it has children", [box1, tb1] {
    auto size = box1->size(1000, 1000);
    assert(size.first > 0);
    assert(size.second == 1);

    auto tsize = tb1->size(1000, 1000);
    assert(tsize.first == size.first);
    assert(tsize.first == size.first);
  });

  it("properly adds left padding", [] {
    Box *b = new Box();
    b->props(Box::Property::padding_left, 2);
    auto size = b->size(1000, 1000);
    assert(size.first == 2);
    assert(size.second == 0);
  });

  it("properly adds right padding", [] {
    Box *b = new Box();
    b->props(Box::Property::padding_right, 2);
    auto size = b->size(1000, 1000);
    assert(size.first == 2);
    assert(size.second == 0);
  });

  it("properly adds top padding", [] {
    Box *b = new Box();
    b->props(Box::Property::padding_top, 2);
    auto size = b->size(1000, 1000);
    assert(size.first == 0);
    assert(size.second == 2);
  });

  it("properly adds bottom padding", [] {
    Box *b = new Box();
    b->props(Box::Property::padding_bottom, 2);
    auto size = b->size(1000, 1000);
    assert(size.first == 0);
    assert(size.second == 2);
  });

  Box *vbox = new Box();
  TextBox *tb = vbox->append<TextBox, const char *>("this is a test string");
  Box *pbox = vbox->append<Box>();
  pbox->props(Box::Property::padding_left, 2);
  pbox->props(Box::Property::padding_right, 2);
  it("places elements vertically with appropriate dimentions", [vbox, tb] {
    auto box_size = vbox->size(1000, 1000);
    auto tb_size = tb->size(1000, 1000);
    assert(
        box_size.first ==
        std::max(tb_size.first, (Box::szu)4)); // + 4 for the Box with padding
    assert(box_size.second == tb_size.second);
  });
}
