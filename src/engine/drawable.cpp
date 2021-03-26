#include "drawable.hpp"

Engine::Drawable::Drawable(WINDOW *window, uint16_t width, uint16_t height) {
  this->window = window;
  this->width = width;
  this->height = height;
}

Engine::Drawable::Kind Engine::Drawable::kind() const { return drawable_kind; }

void Engine::Drawable::handle_event(Event e) {}
