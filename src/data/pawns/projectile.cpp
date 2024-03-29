/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Stefano Volpe #969766
  06/19/2021

  projectile.cpp: implementation of Data::Pawns::Projectile.
*/

#include "projectile.hpp"

#include <cmath>

#include "../../engine/colorable.hpp"
#include "../database.hpp"

using Data::Pawns::Projectile;

Projectile::Projectile(Engine::Color foreground, char character,
                       const Nostd::String &name, int health_damage,
                       int mana_damage, int score_damage, int range,
                       bool casted_by_player, int x, int y)
    : Engine::EntityTile{character, foreground},
      Pawn{name, character, foreground}, hd{health_damage}, md{mana_damage},
      sd{score_damage}, rng{range}, x{x}, y{y}, cbp{casted_by_player} {
  if (std::abs(x) > 1 || std::abs(y) > 1)
    throw std::invalid_argument("Must spawn projectile in an adjacent cell.");
  if (hd < 0)
    throw std::invalid_argument("Health damage must be positive or zero.");
  if (md < 0)
    throw std::invalid_argument("Mana damage must be positive or zero.");
  if (sd < 0)
    throw std::invalid_argument("Score damage must be positive or zero.");
  if (range < 0)
    throw std::invalid_argument("Range must be positive or zero.");
}

bool Projectile::was_casted_by_player() const noexcept { return cbp; }

int Projectile::get_x() const noexcept { return x; }

int Projectile::get_y() const noexcept { return y; }

void Projectile::set_caster(bool caster) noexcept { cbp = caster; }

void Projectile::count_movement() {
  if (is_expired())
    throw std::logic_error("This projectile is already expired.");
  --rng;
}

bool Projectile::is_expired() const noexcept { return !rng; }

int Projectile::unchecked_health_effect(int current_health, int) const {
  return std::max(0, current_health - hd);
}

int Projectile::unchecked_mana_effect(int current_mana, int) const {
  return std::max(0, current_mana - md);
}

int Projectile::unchecked_score_effect(int current_score) const {
  return std::max(0, current_score - sd);
}

std::basic_istream<char> &Data::Pawns::operator>>(std::basic_istream<char> &is,
                                                  Projectile &p) {
  int x;
  (is >> x).ignore();
  int y;
  (is >> y).ignore();
  short foreground;
  (is >> foreground).ignore();
  char character;
  (is >> character).ignore();
  Nostd::String name;
  Data::get_CSV_String(is, name);
  int health_damage, mana_damage, score_damage, range;
  (is >> health_damage).ignore();
  (is >> mana_damage).ignore();
  (is >> score_damage).ignore();
  if (is >> range)
    p = Projectile(Engine::short_to_color(foreground), character, name,
                   health_damage, mana_damage, score_damage, range, false, x,
                   y);
  return is;
}
