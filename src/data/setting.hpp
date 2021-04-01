/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Stefano Volpe #969766
  04/01/2021

  setting.hpp: user interface of Data::Setting.
*/

#ifndef DATA_SETTING_HPP
#define DATA_SETTING_HPP

#include "../nostd/wstring.hpp"

namespace Data {

/*
  A class representing a game setting. It defines both the aspects defined by
  the game designer (label, possible values, and default value) and its current
  state (which can be set by the player).
*/
class Setting {
public:
  class Iterator;

  Setting() = delete;
  // start: lowest possible value
  // size: number of possible values
  // stride: step between possible values
  // default_index: index (starting from 0) of default value
  Setting(int start = 0, size_t size = 2, int stride = 1,
          size_t default_index = 0);
  // value_index: index (starting from 0) of default value. If not specified,
  // it is the same as default_value
  Setting(int start, size_t size, int stride, size_t default_index,
          size_t value_index);

  // move
  Setting(Setting &&) = default;
  Setting &operator=(Setting &&) = default;

  // copy
  Setting(const Setting &) = default;
  Setting &operator=(const Setting &) = default;

  ~Setting() = default;

private:
  Nostd::WString lbl;
  int strt, strd;
  size_t sz, def_ind, val_ind;
};

#endif
