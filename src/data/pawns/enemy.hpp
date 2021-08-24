/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Stefano Volpe #969766
  06/16/2021

  enemy.hpp: user interface of Data::Pawns::Enemy and its helper entities.
*/

#ifndef DATA_PAWNS_ENEMY_HPP
#define DATA_PAWNS_ENEMY_HPP

#include <istream>

#include "../../engine/colorable.hpp"
#include "../../nostd/string.hpp"
#include "character.hpp"
#include "interactable.hpp"

namespace Data {

namespace Pawns {

/*
  An Enemy is an ostile NPC. It is controlled by an AI and is both a Character
  and an Interactable at the same time.
*/
class Enemy : public Character, public Interactable {
public:
  Enemy(Engine::Color foreground, char character, const Nostd::String &name,
        Skill skill, int health_damage, int mana_damage, int score_damage,
        int behavior);
  Enemy(Enemy &&) = default;
  Enemy &operator=(Enemy &&) = default;
  Enemy(const Enemy &) = default;
  Enemy &operator=(const Enemy &) = default;

  ~Enemy() = default;

  bool is_dead() const noexcept;
  void kill() noexcept;

  // A Behavior is a bitmask
  enum class Behavior {
    none = 0,
    walking = 1,
    horizontal_flying = 2,
    vertical_flying = 4,
    attacking = 8
  };

  // Checks whether this Enemy does indeed have a certain behavior
  bool has_behavior(Behavior bhvr) const noexcept;

  friend std::basic_ostream<char> &operator>>(std::basic_ostream<char> &,
                                              const Enemy &);

protected:
  int unchecked_health_effect(int current_health,
                              int max_health) const override final;
  int unchecked_mana_effect(int current_mana,
                            int max_mana) const override final;
  int unchecked_score_effect(int current_score) const override final;

private:
  int hd, md, sd, bhv;
  bool dead = false;
};

// If either a or b has a certain behavior, then so does a | b (and vice versa).
constexpr Enemy::Behavior operator|(Enemy::Behavior a, Enemy::Behavior b);
// If both a and b have a certain behavior, then so does a & b (and vice versa).
constexpr Enemy::Behavior operator&(Enemy::Behavior a, Enemy::Behavior b);

std::basic_istream<char> &operator>>(std::basic_istream<char> &, Enemy &);

} // namespace Pawns

} // namespace Data

#endif
