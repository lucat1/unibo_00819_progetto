#ifndef PAD_BOX_HPP
#define PAD_BOX_HPP

#include "box.hpp"
#include <map>
using namespace std;

namespace Engine {
namespace UI {

enum PAD {
  PADDING_LEFT,
  PADDING_RIGHT,
  PADDING_TOP,
  PADDING_BOTTOM,
};

class PadBox : public Box {
private:
  map<enum PAD, uint16_t> pads = {};
  uint16_t pl = 0, pr = 0, pt = 0, pb = 0;

public:
  PadBox(uint8_t width, uint8_t height, map<enum PAD, uint16_t> pads = {});

  void show(WINDOW *window, uint16_t x, uint16_t y);
  bsize_t size();
};

} // namespace UI
} // namespace Engine

#endif // PAD_BOX_HPP
