#include "colorable.hpp"

int Engine::color_to_int(Color c) noexcept { return static_cast<int>(c); }

auto Engine::Colorable::foreground() const -> Color { return Color::white; }

auto Engine::Colorable::background() const -> Color {
  return Color::transparent;
}
