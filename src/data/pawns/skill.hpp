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
  Skill(const Nostd::String &,
        Nostd::UnorderedMap<Nostd::Pair<int, int>, Projectile> projectiles,
        int healthEffect, bool healthMode);
  Skill(Skill &&) = default;
  Skill &operator=(Skill &&) = default;
  Skill(const Skill &) = default;
  Skill &operator=(const Skill &) = default;

  ~Skill() = default;

  // Each Projectile's key is its spawning coordinates relative to the caster.
  Nostd::UnorderedMap<Nostd::Pair<int, int>, Projectile> &
  projectiles() noexcept;

protected:
  int unchecked_health_effect(int current_health,
                              int max_health) const override final;

private:
  Nostd::UnorderedMap<Nostd::Pair<int, int>, Projectile> p{};
  int he{0}, hm{false};
};

std::basic_istream<char> &operator>>(std::basic_istream<char> &, Skill &);

} // namespace Pawns

} // namespace Data

#endif
