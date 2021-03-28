/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Stefano Volpe #969766
  03/25/2021

  matrix.test.cpp: tests for Nostd::Matrix and its helper entities.
*/

#include "matrix.hpp"
#include <cassert>
#include <iostream>

using namespace Nostd;
using std::cout;

int main() {
  {
    Matrix<int> m1({5, 2, 2}, 1), m2(m1), m3 = m2;
    assert(m1 == m3);
    cout << "\t✓ constructs/copies a Matrix\n";
  }
  {
    Matrix<int> m({5, 6}, 1);
    int sum{0};
    for (auto row : m)
      for (auto cell : row)
        sum += cell.value();
    assert(sum == 30);
    cout << "\t✓ iterates through a Matrix\n";
  }
  {
    Matrix<int> m({3, 4});
    assert(m.order() == 2);
    assert(m.extent(0) == 3 && m.extent(1) == 4);
    assert(m.size() == 12);
    assert(Matrix<int>({}).empty());
    cout << "\t✓ discusses a Matrix's capacity-related qualities\n";
  }
  {
    Matrix<int> m({3, 4, 2});
    m[0][3][1].value() = 2;
    assert(m.data()[7] == 2);
    m.at(1).at(2).at(0).value() = 3;
    assert(m.data()[12] == 3);
    cout << "\t✓ manages references to single cells\n";
  }
  {
    Matrix<int> m1({3, 3}, 1), m2(m1);
    m2.fill(2);
    m1.swap(m2);
    for (auto row : m1)
      for (auto cell : row)
        assert(cell.value() == 2);
    for (auto row : m2)
      for (auto cell : row)
        assert(cell.value() == 1);
    cout << "\t✓ fills and swaps instances of Matrix\n";
  }
}

#include "matrix.cpp"
