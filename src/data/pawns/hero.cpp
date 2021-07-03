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

Hero::Hero(Engine::Color foreground, char character,
           const Nostd::String &name, const Nostd::String &description,
           Skill skill, Skill superSkill, int health, int mana)
    : Engine::EntityTile{character, foreground}, Pawn{name, character,
                                                      foreground},
      Character{name, character, foreground, skill}, dsc{description},
      ssk{superSkill}, curH{health}, maxH{health}, curM{0}, maxM{mana}, scr{0} {
  if (maxH <= 0)
    throw std::invalid_argument("Health must be positive.");
  if (maxM <= 0)
    throw std::invalid_argument("Mana must be positive.");
}

void Hero::rename(const Nostd::String &s) { Pawn::nm = s; }

const Nostd::String &Hero::description() const noexcept { return dsc; }

Mugshot &Hero::mugshot() noexcept { return mug; }

const Mugshot &Hero::mugshot() const noexcept { return mug; }

Skill Hero::superSkill() const noexcept { return ssk; }

void Hero::interact(Interactable &i) {
  curH = i.healthEffect(curH, maxH);
  curM = i.manaEffect(curM, maxM);
  scr = i.scoreEffect(scr);
}

int Hero::currentHealth() const noexcept { return curH; }

int Hero::maxHealth() const noexcept { return maxH; }

bool Hero::isDead() const noexcept { return !curH; }

int Hero::currentMana() const noexcept { return curM; }

int Hero::maxMana() const noexcept { return maxM; }

bool Hero::attemptSuperSkill() noexcept {
  if (curM < maxM)
    return false;
  curM = 0;
  return true;
}

int Hero::score() const noexcept { return scr; }

std::basic_istream<char> &
Data::Pawns::operator>>(std::basic_istream<char> &is, Hero &h) {
  short foreground;
  (is >> foreground).ignore();
  char character;
  (is >> character).ignore();
  Nostd::String name, description;
  Data::get_CSV_String(is, name);
  Data::get_CSV_String(is, description);
  Skill skill, superSkill;
  (is >> skill).ignore();
  (is >> superSkill).ignore();
  int maxHealth, maxMana;
  (is >> maxHealth).ignore();
  if (is >> maxMana) {
    h = Hero(Engine::short_to_color(foreground), character, name, description,
             skill, superSkill, maxHealth, maxMana);
    is.ignore();
  }
  return is;
}
