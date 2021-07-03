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
#include "../../nostd/wstring.hpp"
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
  Enemy(Engine::Color foreground, char character, const Nostd::WString &name,
        Skill skill, int healthDamage, int manaDamage, int scoreDamage,
        int behavior);
  Enemy(Enemy &&) = default;
  Enemy &operator=(Enemy &&) = default;
  Enemy(const Enemy &) = default;
  Enemy &operator=(const Enemy &) = default;

  ~Enemy() = default;

  enum class Behavior {
    none = 0,
    moving = 1,
    gap_aware = 2,
    flying = 4,
    vertical = 8
  };

  bool has_behavior(Behavior bhvr) const noexcept;

  friend std::basic_ostream<char> &operator>>(std::basic_ostream<char> &,
                                                 const Enemy &);

protected:
  int uncheckedHealthEffect(int currentHealth, int maxHealth) override final;
  int uncheckedManaEffect(int currentMana, int maxMana) override final;
  int uncheckedScoreEffect(int currentScore) override final;

private:
  int hD, mD, sD;
  int bhv;
};

constexpr Enemy::Behavior operator|(Enemy::Behavior a, Enemy::Behavior b);
constexpr Enemy::Behavior operator&(Enemy::Behavior a, Enemy::Behavior b);

std::basic_istream<char> &operator>>(std::basic_istream<char> &, Enemy &);

} // namespace Pawns

} // namespace Data

#endif
