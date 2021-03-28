/*
  university of bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Luca Tagliavini #971133
  02/05/2021

  test.hpp: Provides a signle C macro for a simple unit testing experience
  across the whole project. The macro assures scope-isolation and a
  pretty-printed output.
*/
#ifndef TEST_HPP
#define TEST_HPP

#include <iostream>

// Macro used to enclose each test is a separate scope and provide a visual
// feedback when tests are run.
// It is mean to be used with the aim of writing a test which is self-describing
// and easy to read. An example may give a better explaination:
// it("can do a certain thing properly", { /* code */ });
#define it(str, ...)                                                           \
  __VA_ARGS__                                                                  \
  std::cout << "\t✓ " << str << std::endl; \

#endif // TEST_HPP
