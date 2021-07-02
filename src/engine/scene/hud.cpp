/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Luca Tagliavini #971133
  07/02/2021

  hud.hpp: Implements the HUD (Head Up Display) for the whole game scene
*/

#include "hud.hpp"
#include "../../data/palette.hpp"
#include "../screen.hpp"
#include "../ui/text_box.hpp"
#include "../utils.hpp"

Engine::Scene::HUD::HUD(int health, int max_health, int mana, int max_mana) {
  this->health = health;
  this->max_health = max_health;
  this->mana = mana;
  this->max_mana = max_mana;
}

// show creates a new root of components from the Engine::UI namespace which
// will be shown as the HUD visual interface
void Engine::Scene::HUD::show(WINDOW *window, szu x, szu y, szu max_width,
                              szu max_height) {
  Box *root = new Box();
  Nostd::WString health = L"♡ ";
  Utils::stringify(this->health, health);
  health.push_back(L'/');
  Utils::stringify(this->max_health, health);
  auto health_text = root->append<UI::TextBox, const Nostd::WString &>(health);
  health_text->propc(Box::Property::foreground, Data::Palette::health);
  root->show(window, x, y, max_width, max_height);
}

// we're going to display the HUD in one single line on the bottom of the screen
Engine::UI::Box::dim Engine::Scene::HUD::size(szu max_width, szu max_height) {
  return {Screen::columns, 1};
}
