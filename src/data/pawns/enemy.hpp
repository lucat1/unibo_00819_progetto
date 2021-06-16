/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Stefano Volpe #969766
  06/16/2021

  enemy.hpp: user interface of Data::Pawns::Enemy.
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
class Enemy : Character, Interactable {
public:
  Enemy(Engine::Color foreground, wchar_t character, Nostd::WString name,
        Skill skill, int healthDamage, int manaDamage, int scoreDamage);
  Enemy(Enemy &&) = default;
  Enemy &operator=(Enemy &&) = default;
  Enemy(const Enemy &) = default;
  Enemy &operator=(const Enemy &) = default;

  ~Enemy() = default;

  Engine::Color foreground() const noexcept override;
  wchar_t character() const noexcept override;
  const Nostd::WString &name() const noexcept override;
  Skill skill() const noexcept override;

  enum class Behavior {
    none = 0,
    walking = 1,
    gap_aware = 2,
    flying = 4,
    vertical = 8
  };

  bool has_behavior(Behavior bhvr) const noexcept;

  friend std::basic_ostream<wchar_t> &operator>>(std::basic_ostream<wchar_t> &,
                                                 const Enemy &);

protected:
  int uncheckedHealthEffect(int currentHealth, int maxHealth) override;
  int uncheckedManaEffect(int currentMana, int maxMana) override;
  int uncheckedScoreEffect(int currentScore) override;

private:
  Engine::Color fg;
  wchar_t chr;
  Nostd::WString nm{};
  Skill sk;
  int hD, mD, sD;
  Behavior bhvr;
};

constexpr Enemy::Behavior operator|(Enemy::Behavior a, Enemy::Behavior b);
constexpr Enemy::Behavior operator&(Enemy::Behavior a, Enemy::Behavior b);

std::basic_istream<wchar_t> &operator>>(std::basic_istream<wchar_t> &, Enemy &);

} // namespace Pawns

} // namespace Data

#endif
