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
#include "../../nostd/wstring.hpp"
#include "interactable.hpp"

namespace Data {

namespace Pawns {

/*
  A Projectile can be thrown by a Skill in order to inflict indirect damage.
*/
class Projectile : public Interactable {
public:
  Projectile(Engine::Color foreground, wchar_t character,
             const Nostd::WString &name, int healthDamage, int manaDamage,
             int scoreDamage, int range);
  Projectile(Projectile &&) = default;
  Projectile &operator=(Projectile &&) = default;
  Projectile(const Projectile &) = default;
  Projectile &operator=(const Projectile &) = default;

  ~Projectile() = default;

  void countMovement();
  bool isExpired() const noexcept;

  friend std::basic_ostream<wchar_t> &operator>>(std::basic_ostream<wchar_t> &,
                                                 const Projectile &);

protected:
  int uncheckedHealthEffect(int currentHealth, int maxHealth) override final;
  int uncheckedManaEffect(int currentMana, int maxMana) override final;
  int uncheckedScoreEffect(int currentScore) override final;

private:
  int hD, mD, sD, rng;
};

std::basic_istream<wchar_t> &operator>>(std::basic_istream<wchar_t> &,
                                        Projectile &);

} // namespace Pawns

} // namespace Data

#endif
