#include "../../util/test.hpp"
#include "append.hpp"
#include "box.hpp"
#include "text_box.hpp"
#include <assert.h>
using namespace Nostd;
using namespace Engine::UI;

int main() {
  Box *box = new Box(60, 20);
  it("constructs a box properly", {
    assert(box->max_width == 60);
    assert(box->max_height == 20);
    assert(box->first_child == nullptr);
    assert(box->last_child == nullptr);
    assert(box->sibling == nullptr);
    assert(box->parent == nullptr);
  });

  Box *child = new Box(50, 20);
  it("adds a new child", {
    box->add_child(child);
    assert(box->sibling == nullptr);
    assert(box->first_child == child);
    assert(box->last_child == child);
    assert(child->parent == box);

    assert(child->sibling == nullptr);
    assert(child->first_child == nullptr);
    assert(child->last_child == nullptr);
  });

  Box *snd_child = new Box(50, 20);
  it("adds a second child", {
    box->add_child(snd_child);
    assert(box->first_child == child);
    assert(box->last_child == snd_child);
    assert(snd_child->parent == box);
    assert(child->sibling == snd_child);
    assert(snd_child->sibling == nullptr);
  });

  it("Box::append adds a child (with the proper dimentions)", {
    Box *c = append<Box>(box, 0.5f, 0.25f);
    assert(c->parent == box);
    assert(snd_child->sibling == c);
    assert(box->last_child == c);
    assert(c->max_width == (uint16_t)box->max_child_width * 0.5f);
    assert(c->max_height == box->max_child_height * 0.25f);
  });

  it("keeps the child size inside the parent", {
    Box *c = new Box((uint16_t)10000, (uint16_t)10000);
    box->add_child(c);
    assert(c->parent == box);
    assert(c->max_width == box->max_child_width);
    assert(c->max_height == box->max_child_height);
  });

  Box *box1 = new Box(10000, 10000);
  it("reports the corret size when empty", {
    auto size = box1->size();
    assert(size.first == 0);
    assert(size.second == 0);
  });

  TextBox *tb1 = append<TextBox, const wchar_t *>(box1, L"this is a test text");
  it("reports the corret size when it has children", {
    Pair<uint16_t, uint16_t> size = box1->size();
    assert(size.first > 0);
    assert(size.second == 1);

    auto tsize = tb1->size();
    assert(tsize.first == size.first);
    assert(tsize.first == size.first);
  });

  it("properly adds left padding", {
    Box *b = new Box(10, 10);
    b->prop(Box::Property::PADDING_LEFT, 2);
    auto size = b->size();
    assert(size.first == 2);
    assert(size.second == 0);
  });

  it("properly adds right padding", {
    Box *b = new Box(10, 10);
    b->prop(Box::Property::PADDING_RIGHT, 2);
    auto size = b->size();
    assert(size.first == 2);
    assert(size.second == 0);
  });

  it("properly adds top padding", {
    Box *b = new Box(10, 10);
    b->prop(Box::Property::PADDING_TOP, 2);
    auto size = b->size();
    assert(size.first == 0);
    assert(size.second == 2);
  });

  it("properly adds bottom padding", {
    Box *b = new Box(10, 10);
    b->prop(Box::Property::PADDING_BOTTOM, 2);
    auto size = b->size();
    assert(size.first == 0);
    assert(size.second == 2);
  });

  Box *vbox = new Box(50, 4);
  TextBox *tb =
      append<TextBox, const wchar_t *>(vbox, L"this is a test string");
  Box *pbox = append<Box>(vbox);
  pbox->prop(Box::Property::PADDING_LEFT, 2);
  pbox->prop(Box::Property::PADDING_RIGHT, 2);
  it("places elements vertically with appropriate dimentions", {
    Pair<uint16_t, uint16_t> box_size = vbox->size();
    Pair<uint16_t, uint16_t> tb_size = tb->size();
    assert(box_size.first == tb_size.first + 4); // + 4 for the PadBox
    assert(box_size.second == tb_size.second);
  });
}
