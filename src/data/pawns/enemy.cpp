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
      Character{name, character, foreground, skill}, hd{healthDamage},
      md{manaDamage}, sd{scoreDamage}, bhv{behavior} {
  if (hd < 0)
    throw std::invalid_argument("Health damage must be positive.");
  if (md < 0)
    throw std::invalid_argument("Mana damage must be positive.");
  if (sd < 0)
    throw std::invalid_argument("Score damage must be positive.");
}

bool Enemy::is_dead() const noexcept { return dead; }

void Enemy::kill() noexcept { dead = true; }

bool Enemy::has_behavior(Behavior b) const noexcept {
  return bhv & static_cast<int>(b);
}

int Enemy::unchecked_health_effect(int currentHealth, int) const {
  return std::max(0, currentHealth - hd);
}

int Enemy::unchecked_mana_effect(int currentMana, int) const {
  return std::max(0, currentMana - md);
}

int Enemy::unchecked_score_effect(int currentScore) const {
  return std::max(0, currentScore - sd);
}

std::basic_istream<char> &Data::Pawns::operator>>(std::basic_istream<char> &is,
                                                  Enemy &e) {
  if (is) {
    short foreground;
    (is >> foreground).ignore();
    char character;
    (is >> character).ignore();
    Nostd::String name;
    Data::get_CSV_String(is, name);
    if (is) {
      Skill skill;
      (is >> skill).ignore();
      int health_damage, mana_damage, score_damage, behavior;
      (is >> health_damage).ignore();
      (is >> mana_damage).ignore();
      (is >> score_damage).ignore();
      if (is >> behavior) {
        e = Enemy(Engine::short_to_color(foreground), character, name, skill,
                  health_damage, mana_damage, score_damage, behavior);
        is.ignore();
      }
    }
  }
  return is;
}
