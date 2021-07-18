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

Enemy::Enemy(Engine::Color foreground, char character,
             const Nostd::String &name, Skill skill, int healthDamage,
             int manaDamage, int scoreDamage, int behavior)
    : Engine::EntityTile{character, foreground}, Pawn{name, character,
                                                      foreground},
      Character{name, character, foreground, skill}, hD{healthDamage},
      mD{manaDamage}, sD{scoreDamage}, bhv{behavior} {
  if (hD < 0)
    throw std::invalid_argument("Health damage must be positive.");
  if (mD < 0)
    throw std::invalid_argument("Mana damage must be positive.");
  if (sD < 0)
    throw std::invalid_argument("Score damage must be positive.");
}

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

std::basic_istream<char> &Data::Pawns::operator>>(std::basic_istream<char> &is,
                                                  Enemy &e) {
  short foreground;
  (is >> foreground).ignore();
  char character;
  (is >> character).ignore();
  Nostd::String name;
  Data::get_CSV_String(is, name);
  Skill skill;
  int healthDamage, manaDamage, scoreDamage, behavior;
  (is >> skill).ignore();
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
