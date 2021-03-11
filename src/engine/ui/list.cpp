#include "list.hpp"

Engine::UI::List::List(uint8_t width, uint8_t height, wchar_t marker)
    : Box(width, height) {
  this->marker = marker;
}
