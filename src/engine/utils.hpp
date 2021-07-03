/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Luca Tagliavini #971133
  04/27/2021

  utils.hpp: provides some utility functions shared across the engine codebase
*/

#ifndef ENGINE_UTILS_HPP
#define ENGINE_UTILS_HPP

#include "../nostd/wstring.hpp"

namespace Engine {
namespace Utils {

// returns the amount of digits needed to display an integer
int digits(int n);

// converts a number between 0 and 9 (inclusive) to a char charter
char digitize(int n);

// puts the given number in digits inside the provided WString
void stringify(int n, Nostd::WString &str);

// adds left padding (as spaces) to the given string in order to make
// it fill `n` charters.
// NOTE: it can also trim the string if the string's length is greather tha `n`
void leftpad(size_t n, Nostd::WString &str);

} // namespace Utils
} // namespace Engine

#endif // ENGINE_UTILS_HPP
