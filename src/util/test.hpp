#ifndef TEST_HPP
#define TEST_HPP

#include <iostream>

// utility test functions & macros
// just some syntax sugar and a prettier output
#define it(str, ...)                                                           \
  __VA_ARGS__                                                                  \
  std::cout << "\t✓ " << str << std::endl; \

#endif // TEST_HPP
