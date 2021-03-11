#ifndef TEST_HPP
#define TEST_HPP

#include <iostream>
using namespace std;

// utility test functions & macros
// just some syntax sugar and a prettier output
#define it(str, ...)                                                           \
  __VA_ARGS__                                                                  \
  cout << "\t✓ " << str << endl; \

#endif // TEST_HPP
