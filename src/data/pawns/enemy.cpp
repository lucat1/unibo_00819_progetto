/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Stefano Volpe #969766
  06/16/2021

  enemy.cpp: implementation of Data::Pawns::Enemy and its helper entities.
*/

#include "enemy.hpp"

#include <algorithm>

#include "../../engine/colorable.hpp"
#include "../database.hpp"

using Data::Pawns::Enemy;

Enemy::Enemy(Engine::Color foreground, wchar_t character,
             const Nostd::WString &name, Skill skill, int healthDamage,
             int manaDamage, int scoreDamage, int behavior)
    : fg{foreground}, chr{character}, nm{name}, sk{skill}, hD{healthDamage},
      mD{manaDamage}, sD{scoreDamage}, bhv{behavior} {
  if (hD < 0)
    throw std::invalid_argument("Health damage must be positive.");
  if (mD < 0)
    throw std::invalid_argument("Mana damage must be positive.");
  if (sD < 0)
    throw std::invalid_argument("Score damage must be positive.");
}

Engine::Color Enemy::foreground() const noexcept { return fg; }

wchar_t Enemy::character() const noexcept { return chr; }

const Nostd::WString &Enemy::name() const noexcept { return nm; }

auto Enemy::skill() const noexcept -> Skill { return sk; }

bool Enemy::has_behavior(Behavior b) const noexcept {
  return bhv & static_cast<int>(b);
}

int Enemy::uncheckedHealthEffect(int currentHealth, int) {
  return std::max(0, currentHealth - hD);
}

int Enemy::uncheckedManaEffect(int currentMana, int) {
  return std::max(0, currentMana - mD);
}

int Enemy::uncheckedScoreEffect(int currentScore) {
  return std::max(0, currentScore - sD);
}

std::basic_istream<wchar_t> &
Data::Pawns::operator>>(std::basic_istream<wchar_t> &is, Enemy &e) {
  short foreground;
  (is >> foreground).ignore();
  wchar_t character;
  (is >> character).ignore();
  Nostd::WString name;
  Data::get_CSV_WString(is, name);
  Skill skill;
  (is >> skill).ignore();
  int healthDamage, manaDamage, scoreDamage, behavior;
  (is >> healthDamage).ignore();
  (is >> manaDamage).ignore();
  (is >> scoreDamage).ignore();
  if (is >> behavior) {
    e = Enemy(Engine::short_to_color(foreground), character, name, skill,
              healthDamage, manaDamage, scoreDamage, behavior);
    is.ignore();
  }
  return is;
}
