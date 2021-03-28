/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Stefano Volpe #969766
  03/18/2021

  test.hpp: utilities for testing purposes only.
*/

#ifndef NOSTD_TEST_HPP
#define NOSTD_TEST_HPP

#include <iostream>

namespace Nostd {

// Executes the "test" parameter and neatly prints the related message
// afterwards. Examples:
// it("passes the 'f function' test", f);
// it("passes a very easy test", []() { assert(2 + 2 == 4); });
inline void it(const char *str, void test()) {
  test();
  std::cout << "\t✓ " << str << '\n';
}

} // namespace Nostd

#endif
