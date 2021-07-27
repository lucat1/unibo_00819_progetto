/*
  university of bologna
  first cicle degree in computer science
  00819 - programmazione

  luca tagliavini #971133
  07/27/2021

  audio.cpp: implements the logic for audio-playing using the `aplay` and
  `afplay` system tools
*/

#include "audio.hpp"

void Engine::Audio::fetch_tool() {}

int Engine::Audio::play(const char *fp) {
  if (tool == nullptr)
    fetch_tool();

  return 1;
}

void Engine::Audio::stop() {}
