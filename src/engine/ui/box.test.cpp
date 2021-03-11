#include "../../util/test.hpp"
#include "box.hpp"
#include <assert.h>
using namespace Engine::UI;

int main() {
  Box *box = new Box(60, 20);
  it("constructs a box properly", {
    assert(box->width == 60);
    assert(box->height == 20);
    assert(box->children == nullptr);
    assert(box->sibling == nullptr);
    assert(box->parent == nullptr);
  });

  Box *child = new Box(50, 20);
  it("adds a new child", {
    box->add_child(child);
    assert(box->sibling == nullptr);
    assert(box->children == child);

    assert(child->sibling == nullptr);
    assert(child->children == nullptr);
    assert(child->parent == box);
  });

  Box *snd_child = new Box(50, 20);
  it("adds a second child", {
    box->add_child(snd_child);
    assert(box->children == snd_child);
    assert(snd_child->parent == box);
    assert(snd_child->sibling == child);
    assert(child->sibling == nullptr);
  });

  it("adds a child Box::append with the proper dimentions", {
    Box *c = Box::append(box, 0.5f, 0.25f);
    assert(c->parent == box);
    assert(c->sibling == snd_child);
    assert(c->width == box->width * 0.5f);
    assert(c->height == box->height * 0.25f);
  });
}
