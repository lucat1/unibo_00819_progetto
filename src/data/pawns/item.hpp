/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Stefano Volpe #969766
  06/17/2021

  item.hpp: user interface of Data::Pawns::Item.
*/

#ifndef DATA_PAWNS_ITEM_HPP
#define DATA_PAWNS_ITEM_HPP

#include <istream>

#include "../../engine/colorable.hpp"
#include "../../nostd/wstring.hpp"
#include "interactable.hpp"
#include "pawn.hpp"

namespace Data {

namespace Pawns {

/*
  An Item is a helpful, consumable Interactable which can increase health, mana,
  and score. "Modes" are false when their respective bonuses are absolute
  values, and true when their respective bonuses are percentages.
*/
class Item : public Interactable {
public:
  Item(Engine::Color foreground, wchar_t character, const Nostd::WString &name,
       int healthBonus, bool healthMode, int manaBonus, bool manaMode,
       int scoreBonus);
  Item(Item &&) = default;
  Item &operator=(Item &&) = default;
  Item(const Item &) = default;
  Item &operator=(const Item &) = default;

  ~Item() = default;

  friend std::basic_ostream<wchar_t> &operator>>(std::basic_ostream<wchar_t> &,
                                                 const Item &);

protected:
  int uncheckedHealthEffect(int currentHealth, int maxHealth) override final;
  int uncheckedManaEffect(int currentMana, int maxMana) override final;
  int uncheckedScoreEffect(int currentScore) override final;

private:
  int hB, mB, sB;
  bool hM, mM;
};

std::basic_istream<wchar_t> &operator>>(std::basic_istream<wchar_t> &, Item &);

} // namespace Pawns

} // namespace Data

#endif
