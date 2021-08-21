/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Stefano Volpe #969766
  06/14/2021

  hero.cpp: implementation of Data::Pawns::Hero.
*/

#include "hero.hpp"

#include <stdexcept>

#include "../../engine/colorable.hpp"
#include "../../nostd/string.hpp"
#include "../database.hpp"
#include "skill.hpp"

using Data::Mugshot;
using Data::Pawns::Hero;
using Data::Pawns::Interactable;
using Data::Pawns::Skill;

Hero::Hero(Engine::Color foreground, char character, const Nostd::String &name,
           const Nostd::String &description, Skill skill, Skill superSkill,
           int health, int mana)
    : Engine::EntityTile{character, foreground}, Pawn{name, character,
                                                      foreground},
      Character{name, character, foreground, skill, true}, dsc{description},
      ssk{superSkill}, curH{health}, maxH{health}, curM{0}, maxM{mana}, scr{0} {
  if (maxH <= 0)
    throw std::invalid_argument("Health must be positive.");
  if (maxM <= 0)
    throw std::invalid_argument("Mana must be positive.");
  for (auto &x : ssk.projectiles())
    x->second.set_caster(true);
}

void Hero::rename(const Nostd::String &s) { Pawn::nm = s; }

const Nostd::String &Hero::description() const noexcept { return dsc; }

Mugshot &Hero::mugshot() noexcept { return mug; }

const Mugshot &Hero::mugshot() const noexcept { return mug; }

Skill Hero::superskill() const noexcept { return ssk; }

void Hero::interact(Interactable &i) {
  curH = i.health_effect(curH, maxH);
  curM = i.mana_effect(curM, maxM);
  scr = i.score_effect(scr);
}

int Hero::current_health() const noexcept { return curH; }

int Hero::max_health() const noexcept { return maxH; }

bool Hero::is_dead() const noexcept { return !curH; }

int Hero::current_mana() const noexcept { return curM; }

int Hero::max_mana() const noexcept { return maxM; }

bool Hero::attempt_super_skill() noexcept {
  if (curM < maxM)
    return false;
  curM = 0;
  return true;
}

int Hero::score() const noexcept { return scr; }

std::basic_istream<char> &Data::Pawns::operator>>(std::basic_istream<char> &is,
                                                  Hero &h) {
  if (is) {
    short foreground;
    (is >> foreground).ignore();
    char character;
    (is >> character).ignore();
    Nostd::String name, description;
    Data::get_CSV_String(is, name);
    Data::get_CSV_String(is, description);
    if (is) {
      Skill skill, superskill;
      (is >> skill).ignore();
      (is >> superskill).ignore();
      int maxHealth, max_mana;
      (is >> maxHealth).ignore();
      if (is >> max_mana) {
        h = Hero(Engine::short_to_color(foreground), character, name,
                 description, skill, superskill, maxHealth, max_mana);
        is.ignore();
      }
    }
  }
  return is;
}
