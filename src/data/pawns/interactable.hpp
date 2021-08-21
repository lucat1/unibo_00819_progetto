/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Stefano Volpe #969766
  06/14/2021

  interactable.hpp: user interface of Data::Pawns::Interactable.
*/

#ifndef DATA_PAWNS_INTERACTABLE_HPP
#define DATA_PAWNS_INTERACTABLE_HPP

#include "pawn.hpp"

namespace Data {

namespace Pawns {

/*
  An Interactable affects the Hero directly contolled by the player when they
  come in contact. The effect caused by this interaction may be either positive,
  or negative.
*/
class Interactable : public virtual Pawn {
public:
  Interactable() = default;
  Interactable(Interactable &&) = default;
  Interactable &operator=(Interactable &&);
  Interactable(const Interactable &) = default;
  Interactable &operator=(const Interactable &) = default;

  // These methods validate their argument and return the new stats after the
  // interaction.
  int health_effect(int currentHealth, int maxHealth);
  int mana_effect(int currentMana, int maxMana);
  int score_effect(int currentScore);

protected:
  // These methods do not validare their argument and return the new stats after
  // the interaction.
  virtual int unchecked_health_effect(int currentHealth, int maxHealth);
  virtual int unchecked_mana_effect(int currentMana, int maxMana);
  virtual int unchecked_score_effect(int currentScore);
};

} // namespace Pawns

} // namespace Data

#endif
