#include "../util/test.hpp"
#include "vector.hpp"
using namespace Nostd;

int main() {
  Vector<int> vec;
  vec.push_back(3);
  vec.push_back(8);
  vec.push_back(9);
  vec.push_back(40);
  vec.push_back(79);
  vec.push_back(390);
  vec.push_back(9576);
  vec.push_back(437895);
  for (size_t i = 0; i < vec.size(); i++) {
    cout << vec.at(i) << endl;
  }
}