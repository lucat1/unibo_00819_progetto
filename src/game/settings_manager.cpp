/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Andreea Scrob #989372
  08/12/2021

  settings_manager.cpp: implementation of Game::SettingsManager.
*/

#include "settings_manager.hpp"
#include "../engine/audio.hpp"
#include <iostream>

using Engine::Audio;
using Game::SettingsManager;
using std::cout;

SettingsManager::SettingsManager(const Data::Database &datab) : db(datab) {}

bool SettingsManager::get_sound() { return sound; }

int SettingsManager::play_soundtrack(const char fn[]) {
  if (sound) {
    auto fp = db.to_audio_filepath(fn);
    switch (Audio::play(fp.c_str())) {
    case Audio::Error::none:
      return 0;
    case Audio::Error::no_tool:
      cout << "Could not play the soundtrack. Do you have aplay or afplay?\n";
      return 1;
    case Audio::Error::invalid_file:
      cout << "Could not play the soundtrack: invalid file (" << fp << ").\n";
      return 2;
    default:
      cout << "Could not play the soundtrack: unknown error.\n";
      return 3;
    }
  }
  return 0;
}

int SettingsManager::get_fps() { return fps; }

void SettingsManager::apply_settings() {
  for (auto x : db.settings()) {
    if (x.label() == "Sounds") {
      sound = *x.current_value();
      if (!sound)
        Audio::stop();
      else if (Audio::status() == Audio::State::stopped)
        play_soundtrack("main_menu");
    } else if (x.label() == "Frames per second")
      fps = *x.current_value();
  }
}