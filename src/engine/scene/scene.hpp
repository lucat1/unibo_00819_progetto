/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Luca Tagliavini #971133
  07/02/2021

  scene.hpp: Defines the Engine::Scene::Screne class, the main game rendering facility.
  This class implements the Engine::Drawable interface like all Engine::Menu::* classes
  to be displayed inside the usual Engine::Screen session.
*/

#ifndef ENGINE_SCENE_SCRENE_HPP
#define ENGINE_SCENE_SCRENE_HPP

#include "../drawable.hpp"
#include "../../data/pawns/hero.hpp"

namespace Engine {
namespace Scene {

class Scene : public Drawable {
private:
  /* const Data::Pawns::Hero &player; */
  Data::Pawns::Hero player;

  void draw();

public:
  Kind kind() const;
  void handle_event(Event e);

  Scene(WINDOW *window);
};

} // namespace Scene
} // namespace Engine

#endif // ENGINE_SCENE_SCRENE_HPP
