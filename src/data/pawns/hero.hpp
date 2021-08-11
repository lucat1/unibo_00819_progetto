/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Stefano Volpe #969766
  06/14/2021

  hero.hpp: user interface of Data::Pawns::Hero.
*/

#ifndef DATA_PAWNS_HERO_HPP
#define DATA_PAWNS_HERO_HPP

#include <istream>

#include "../../engine/colorable.hpp"
#include "../../nostd/string.hpp"
#include "../mugshot.hpp"
#include "character.hpp"
#include "interactable.hpp"

namespace Data {

namespace Pawns {

/*
  A Hero is a playable character: as such, it provides a health and a mana
  gauges, as well as a description and an additional skill.
*/
class Hero : public Character {
public:
  Hero(Engine::Color foreground, char character, const Nostd::String &name,
       const Nostd::String &description, Skill skill, Skill superSkill,
       int maxHealth, int maxMana);
  Hero(Hero &&) = default;
  Hero &operator=(Hero &&) = default;
  Hero(const Hero &) = default;
  Hero &operator=(const Hero &) = default;

  virtual ~Hero() = default;

  void rename(const Nostd::String &); // you can rename the Hero you play as
  const Nostd::String &description() const noexcept;
  Mugshot &mugshot() noexcept;
  const Mugshot &mugshot() const noexcept;
  Skill superSkill() const noexcept;
  void interact(Interactable &); // applies the effect of an Interactable
  int currentHealth() const noexcept;
  int maxHealth() const noexcept;
  bool isDead() const noexcept; // checks if the game is over
  int currentMana() const noexcept;
  int maxMana() const noexcept;
  // if mana is full, sets it to zero and returns true
  bool attemptSuperSkill() noexcept;
  int score() const noexcept;

  friend std::basic_ostream<char> &operator>>(std::basic_ostream<char> &,
                                              const Hero &);

private:
  Nostd::String dsc{};
  Mugshot mug{};
  Skill ssk;
  int curH, maxH, curM, maxM, scr;
};

std::basic_istream<char> &operator>>(std::basic_istream<char> &, Hero &);

} // namespace Pawns

} // namespace Data

#endif
