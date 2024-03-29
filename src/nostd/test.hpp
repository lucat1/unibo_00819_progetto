/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Stefano Volpe #969766
  03/18/2021

  test.hpp: user interface of the utilities for testing purposes only.
*/

#ifndef NOSTD_TEST_HPP
#define NOSTD_TEST_HPP

#include <functional>

namespace Nostd {

// Executes the "test" parameter and neatly prints the related message
// afterwards. Examples:
// it("passes the 'f function' test", f);
// it("passes a very easy test", []() { assert(2 + 2 == 4); });
void it(const char *str, std::function<void()> test);

} // namespace Nostd

#endif // NOSTD_TEST_HPP
