#ifndef TEXT_BOX_HPP
#define TEXT_BOX_HPP

#include "box.hpp"
#include <vector>
using namespace std;

namespace Engine {
namespace UI {

class TextBox : public Box {
private:
  wchar_t *content;
  vector<wchar_t *> split_content();

public:
  TextBox(uint8_t width, uint8_t height, wchar_t *content);

  // FIXME: devo davvero ridefinirlo volpe?
  // cpp is a joke
  void show(uint16_t x, uint16_t y);
  static TextBox append(Box box);
};

} // namespace UI
} // namespace Engine

#endif // TEXT_BOX_HPP
