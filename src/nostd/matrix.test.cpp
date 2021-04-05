/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Stefano Volpe #969766
  03/25/2021

  matrix.test.cpp: tests for Nostd::Matrix and its helper entities.
*/

#include <cassert>

#include "matrix.hpp"
#include "test.hpp"

using namespace Nostd;

int main() {
  it("constructs/copies a Matrix", [] {
    Matrix<int> m1({5, 2, 2}, 1), m2(m1), m3 = m2;
    assert(m1 == m3);
  });
  it("iterates through a Matrix", [] {
    Matrix<int> m({5, 6}, 1);
    int sum{0};
    for (auto row : m)
      for (auto cell : row)
        sum += cell.value();
    assert(sum == 30);
  });
  it("discusses a Matrix's capacity-related qualities", [] {
    Matrix<int> m({3, 4});
    assert(m.order() == 2);
    assert(m.extent(0) == 3 && m.extent(1) == 4);
    assert(m.size() == 12);
    assert(Matrix<int>({}).empty());
  });
  it("manages references to single cells", [] {
    Matrix<int> m({3, 4, 2});
    m[0][3][1].value() = 2;
    assert(m.data()[7] == 2);
    m.at(1).at(2).at(0).value() = 3;
    assert(m.data()[12] == 3);
  });
  it("fills and swaps instances of Matrix", [] {
    Matrix<int> m1({3, 3}, 1), m2(m1);
    m2.fill(2);
    m1.swap(m2);
    for (auto row : m1)
      for (auto cell : row)
        assert(cell.value() == 2);
    for (auto row : m2)
      for (auto cell : row)
        assert(cell.value() == 1);
  });
}

#include "matrix.cpp"
