/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Stefano Volpe #969766
  06/20/2021

  skill.hpp: user interface of Data::Pawns::Skill.
*/

#ifndef DATA_PAWNS_SKILL_HPP
#define DATA_PAWNS_SKILL_HPP

#include <istream>

#include "../../nostd/pair.hpp"
#include "../../nostd/unordered_map.hpp"
#include "interactable.hpp"
#include "projectile.hpp"

namespace Data {

namespace Pawns {

/*
  A Skill specifies the way Projectiles can be spawned and their effects on the
  agent spawning them.
*/
class Skill : public Interactable {
public:
  Skill() = default; // uneffective skill: does nothing at all
  Skill(Nostd::UnorderedMap<Nostd::Pair<int, int>, Projectile> projectiles,
        int healthEffect, bool healthMode);
  Skill(Skill &&) = default;
  Skill &operator=(Skill &&) = default;
  Skill(const Skill &) = default;
  Skill &operator=(const Skill &) = default;

  ~Skill() = default;

  // Each Projectile's key is its spawning coordinates relative to the caster.
  const Nostd::UnorderedMap<Nostd::Pair<int, int>, Projectile> &
  projectiles() const noexcept;

protected:
  int uncheckedHealthEffect(int currentHealth, int maxHealth) override final;

private:
  Nostd::UnorderedMap<Nostd::Pair<int, int>, Projectile> p{};
  int hE{0}, hM{false};
};

std::basic_istream<char> &operator>>(std::basic_istream<char> &, Skill &);

} // namespace Pawns

} // namespace Data

#endif
