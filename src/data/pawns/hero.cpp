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
#include "../../nostd/wstring.hpp"
#include "../database.hpp"
#include "skill.hpp"

using Data::Pawns::Hero;
using Data::Pawns::Interactable;
using Data::Pawns::Result;
using Data::Pawns::Skill;

Hero::Hero(Engine::Color foreground, wchar_t character, Nostd::WString name,
           Nostd::WString description, Skill skill, Skill superSkill,
           int health, int mana)
    : fg{foreground}, chr{character}, nm{name}, dsc{description}, sk{skill},
      ssk{superSkill}, curH{health}, maxH{health}, curM{0}, maxM{mana}, scr{0} {
  if (maxH <= 0)
    throw std::invalid_argument("Health must be positive.");
  if (maxM <= 0)
    throw std::invalid_argument("Mana must be positive.");
}

Engine::Color Hero::foreground() const noexcept { return fg; }

wchar_t Hero::character() const noexcept { return chr; }

const Nostd::WString &Hero::name() const noexcept { return nm; }

Skill Hero::skill() const noexcept { return sk; }

void Hero::rename(const Nostd::WString &s) { nm = s; }

const Nostd::WString &Hero::description() const noexcept { return dsc; }

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

Hero::operator Result() const { return Result(nm, scr, fg, chr); }

std::basic_istream<wchar_t> &operator>>(std::basic_istream<wchar_t> &is,
                                        Hero &h) {
  short foreground;
  (is >> foreground).ignore();
  wchar_t character;
  (is >> character).ignore();
  Nostd::WString name, description;
  Data::get_CSV_WString(is, name);
  Data::get_CSV_WString(is, description);
  Skill skill, superSkill;
  (is >> skill).ignore();
  (is >> superSkill).ignore();
  int maxHealth, maxMana;
  is >> maxHealth >> maxMana;
  is.ignore();
  if (is)
    h = Hero(Engine::short_to_color(foreground), character, name, description,
             skill, superSkill, maxHealth, maxMana);
  return is;
}
