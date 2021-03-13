#include "pad_box.hpp"
using namespace Engine::UI;

PadBox::PadBox(uint8_t width, uint8_t height, map<enum PAD, uint16_t> pads)
    : Box(width, height) {
  this->pads = pads;
  for (map<enum PAD, uint16_t>::iterator it = pads.begin(); it != pads.end();
       it++) {
    switch (it->first) {
    case PADDING_LEFT:
      pl = it->second;
    case PADDING_RIGHT:
      pr = it->second;
    case PADDING_TOP:
      pt = it->second;
    case PADDING_BOTTOM:
      pb = it->second;
    }
  }

  this->width = width - this->pl - this->pr;
  this->height = width - this->pt - this->pb;
}

// Creates a new PadBox instance and adds it to the target Box's children.
PadBox *PadBox::append(Box *target, float w, float h,
                       map<enum PAD, uint16_t> pads) {
  PadBox *box = new PadBox(target->width * w, target->height * h, pads);
  target->add_child(box);
  return box;
}

void PadBox::show(WINDOW *window, uint16_t x, uint16_t y) {
  Box *iter = this->first_child;
  uint8_t next_y = y, max_y = pt + y + height;
  while (iter != NULL) {
    // don't render items outside of this Box
    // TODO: scrollbars (?)
    if (next_y + iter->height > max_y) {
      break;
    }

    iter->show(window, x + pl, next_y + pt);
    next_y = next_y + iter->height;
    iter = iter->sibling;
  }
}
