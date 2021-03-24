#include "colorable.hpp"

short Engine::color_to_short(Color c) noexcept { return static_cast<short>(c); }

Engine::Color Engine::short_to_color(short c) noexcept {
  return static_cast<Engine::Color>(c);
}

auto Engine::Colorable::foreground() const -> Color { return Color::white; }

auto Engine::Colorable::background() const -> Color {
  return Color::transparent;
}
