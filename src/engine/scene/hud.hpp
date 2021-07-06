/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Luca Tagliavini #971133
  07/02/2021

  hud.cpp: Defines the Engine::Scene::HUD definition. This class provides a
  visual element
*/

#ifndef ENGINE_SCENE_HUD_HPP
#define ENGINE_SCENE_HUD_HPP

#include "../ui/box.hpp"

namespace Engine {
namespace Scene {

class HUD : public UI::Box {
private:
  int health, max_health, mana, max_mana, score;
  void bar(WINDOW *window, szu x, szu y, int value, int max_value, const char* icon, Color c);

public:
  HUD(int health, int max_health, int mana, int max_mana , int score);

  void show(WINDOW *window, szu x, szu y, szu max_width, szu max_height);
  dim size(szu max_width, szu max_height);
};

} // namespace Scene
} // namespace Engine

#endif // ENGINE_SCENE_HUD_HPP
