/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Luca Tagliavini #971133
  07/02/2021

  scene.hpp: Defines the Engine::Scene::Screne class, the main game rendering
  facility. This class implements the Engine::Drawable interface like all
  Engine::Menu::* classes to be displayed inside the usual Engine::Screen
  session.
*/

#ifndef ENGINE_SCENE_SCRENE_HPP
#define ENGINE_SCENE_SCRENE_HPP

#include "../../world/world.hpp"
#include "hud.hpp"

namespace Engine {
namespace Scene {

class Scene : public Drawable {
private:
  static const int threshold = 10;
  const World::World &world;
  HUD hud;
  bool over = false;

  void draw();
  void draw_chunk(const Nostd::Matrix<Tile *> &tiles,
                  const Nostd::Matrix<Data::Pawns::Enemy *> &enemies,
                  const Nostd::Matrix<Data::Pawns::Item *> &items,
                  const Nostd::Matrix<Data::Pawns::Projectile *> &porjectiles,
                  int x, int y, int offset_x = 0, int offset_y = 0);

public:
  static const szu width = Screen::columns;
  static const szu height = Screen::lines - 1; // one line reserved for the HUD

  Kind kind() const;
  void handle_event(Event e);
  bool is_over();

  Scene(WINDOW *window, const World::World &world,
        const Nostd::String &message);
};

} // namespace Scene
} // namespace Engine

#endif // ENGINE_SCENE_SCRENE_HPP
