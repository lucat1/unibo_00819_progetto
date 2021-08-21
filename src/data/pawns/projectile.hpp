/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Stefano Volpe #969766
  06/17/2021

  projectile.hpp: user interface of Data::Pawns::Projectile.
*/

#ifndef DATA_PAWNS_PROJECTILE_HPP
#define DATA_PAWNS_PROJECTILE_HPP

#include <istream>

#include "../../engine/colorable.hpp"
#include "../../nostd/string.hpp"
#include "interactable.hpp"

namespace Data {

namespace Pawns {

/*
  A Projectile can be thrown by a Skill in order to inflict indirect damage.
*/
class Projectile : public Interactable {
public:
  Projectile(Engine::Color foreground, char character,
             const Nostd::String &name, int health_damage, int mana_damage,
             int score_damage, int range, bool casted_by_player = false);
  Projectile(Projectile &&) = default;
  Projectile &operator=(Projectile &&) = default;
  Projectile(const Projectile &) = default;
  Projectile &operator=(const Projectile &) = default;

  ~Projectile() = default;

  bool was_casted_by_player() const noexcept;
  void count_movement();
  bool is_expired() const noexcept;

  friend std::basic_ostream<char> &operator>>(std::basic_ostream<char> &,
                                              const Projectile &);

protected:
  int unchecked_health_effect(int current_health,
                              int max_health) override final;
  int unchecked_mana_effect(int current_mana, int max_mana) override final;
  int unchecked_score_effect(int current_score) override final;

private:
  int hd, md, sd, rng;
  bool cbp;
};

std::basic_istream<char> &operator>>(std::basic_istream<char> &, Projectile &);

} // namespace Pawns

} // namespace Data

#endif
