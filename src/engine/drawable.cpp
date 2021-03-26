#include "drawable.hpp"

Engine::Drawable::Drawable(WINDOW *window) { this->window = window; }

Engine::Drawable::Kind Engine::Drawable::kind() const {
  return Engine::Drawable::Kind::none;
}

void Engine::Drawable::handle_event(Event e) {}
