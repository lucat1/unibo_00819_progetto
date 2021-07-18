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
  // TODO: refactor with the proper world structure
  const Data::Pawns::Hero &player;
  // TODO: remove this functionality, the world structure will contain a way to
  // notify us that the game has ended
  bool over = false;

  void draw();

public:
  Kind kind() const;
  void handle_event(Event e);
  bool is_over();

  Scene(WINDOW *window, const Data::Pawns::Hero &hero);
};

} // namespace Scene
} // namespace Engine

#endif // ENGINE_SCENE_SCRENE_HPP
