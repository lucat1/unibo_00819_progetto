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
#include "../../nostd/string.hpp"
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
  Item(Engine::Color foreground, char character, const Nostd::String &name,
       int health_bonus, bool health_mode, int mana_bonus, bool mana_mode,
       int score_bonus);
  Item(Item &&) = default;
  Item &operator=(Item &&) = default;
  Item(const Item &) = default;
  Item &operator=(const Item &) = default;

  ~Item() = default;

  friend std::basic_ostream<char> &operator>>(std::basic_ostream<char> &,
                                              const Item &);

protected:
  int unchecked_health_effect(int current_health,
                              int max_health) override final;
  int unchecked_mana_effect(int current_mana, int max_mana) override final;
  int unchecked_score_effect(int current_score) override final;

private:
  int hb, mb, sb;
  bool hm, mm;
};

std::basic_istream<char> &operator>>(std::basic_istream<char> &, Item &);

} // namespace Pawns

} // namespace Data

#endif
