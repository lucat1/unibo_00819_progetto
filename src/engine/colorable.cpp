#include "colorable.hpp"

short Engine::color_to_short(Color c) noexcept { return static_cast<short>(c); }

Engine::Color Engine::short_to_color(short c) noexcept {
  return static_cast<Engine::Color>(c);
}

Engine::Color Engine::Colorable::foreground() const { return Color::white; }

Engine::Color Engine::Colorable::background() const {
  return Color::transparent;
}
