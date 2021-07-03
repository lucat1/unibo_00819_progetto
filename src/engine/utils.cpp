/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Luca Tagliavini #971133
  04/27/2021

  screen.cpp: implements engine's utility functions mainly to manipulate
  integers and strings, for the choice ui element and the results menu
*/

#include "utils.hpp"

int Engine::Utils::digits(int n) {
  int k = 0;
  while (n > 0) {
    k++;
    n /= 10;
  }

  return k;
}

char Engine::Utils::digitize(int n) {
  if (n > 9)
    return u'-'; // undefined behaviour

  return u'0' + n;
}

void Engine::Utils::stringify(int n, Nostd::WString &str) {
  if (n == 0)
    str.insert(str.length(), u'0');
  else {
    if (n < 0) {
      str.insert(0, u'-');
      n = -n; // make it positive
    }
    int last = str.length();
    while (n > 0) {
      str.insert(last, digitize(n % 10));
      n /= 10;
    }
  }
}

void Engine::Utils::leftpad(size_t n, Nostd::WString &str) {
  size_t len = str.length();
  if (len > n) {
    str = str.substr(0, n - 1);
  } else if (len != n) {
    size_t amount = n - len;
    char space[amount + 1];
    // fill the space string with the right amount of spaces
    for (size_t i = 0; i < amount; i++)
      space[i] = u' ';
    space[amount] = '\0';

    str.insert(0, space, amount);
  }
}
