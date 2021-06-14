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
  An Interactable is a Pawn which affects the one directly contolled by the
  player when they come in contact. The effect caused by this interaction may be
  either positive, or negative.
*/
class Interactable : public Pawn {
public:
  // These methods validate their argument and return the new stats after the
  // interaction.
  int healthEffect(int currentHealth, int maxHealth);
  int manaEffect(int currentMana, int maxMana);
  int scoreEffect(int currentScore);

protected:
  // These methods do not validare their argument and return the new stats after
  // the interaction.
  virtual int uncheckedHealthEffect(int currentHealth, int maxHealth);
  virtual int uncheckedManaEffect(int currentMana, int maxMana);
  virtual int uncheckedScoreEffect(int currentScore);
};

} // namespace Pawns

} // namespace Data

#endif
