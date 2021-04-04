/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Luca Tagliavini #971133
  03/20/2021

  drawable.cpp: Implements the default methods for the abstract class
  Engine::Drawable.
*/
#include "drawable.hpp"

Engine::Drawable::Drawable(WINDOW *window, uint16_t width, uint16_t height) {
  this->window = window;
  this->width = width;
  this->height = height;
}
Engine::Drawable::~Drawable() {}

Engine::Drawable::Kind Engine::Drawable::kind() const { return drawable_kind; }

void Engine::Drawable::handle_event(Event e) {}

bool Engine::Drawable::is_over() { return false; }
