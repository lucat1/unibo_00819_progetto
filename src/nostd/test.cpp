/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Stefano Volpe #969766
  03/29/2021

  test.cpp: implementation of the utilities for testing purposes only.
*/

#include "test.hpp"
#include <iostream>

void Nostd::it(const char *str, std::function<void()> test) {
  test();
  std::cout << "\t✓ " << str << '\n';
}
