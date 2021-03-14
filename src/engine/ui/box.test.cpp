#include "../../util/test.hpp"
#include "append.hpp"
#include "box.hpp"
#include "text_box.hpp"
#include <assert.h>
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
    assert(c->max_width == (uint16_t)box->max_width * 0.5f);
    assert(c->max_height == box->max_height * 0.25f);
  });

  it("keeps the child size inside the parent", {
    Box *c = new Box((uint16_t)10000, (uint16_t)10000);
    box->add_child(c);
    assert(c->parent == box);
    assert(c->max_width == box->max_width);
    assert(c->max_height == box->max_height);
  });

  Box *box1 = new Box(10000, 10000);
  it("reports the corret size when empty", {
    Pair<uint16_t, uint16_t> size = box1->size();
    assert(size.first == 0);
    assert(size.second == 0);
  });

  TextBox *tb1 =
      append<TextBox, const wchar_t *>(box1, 1, 1, L"this is a test text");
  it("reports the corret size when it has children", {
    Pair<uint16_t, uint16_t> size = box1->size();
    assert(size.first > 0);
    assert(size.second == 1);

    Pair<uint16_t, uint16_t> tsize = tb1->size();
    assert(tsize.first == size.first);
    assert(tsize.first == size.first);
  });
}
