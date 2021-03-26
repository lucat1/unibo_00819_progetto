#include "tree_map.hpp"
#include <iostream>

using namespace std;

int main() {
  cout << "=============TREEMAP TEST=============" << endl;
  Nostd::TreeMap<int, int> ma;
  cout << "[] add" << endl;
  ma.add(2, 3);
  ma.add(4, 5);
  ma.add(1, 23);
  cout << "[] operator []" << endl;
  cout << ma[4] << endl;
  cout << "[] get values" << endl;
  auto v = ma.get_values();
  cout << v.size() << endl;
  cout << "[] remove" << endl;
  ma.remove(1);
  cout << "[] get values" << endl;
  v = ma.get_values();
  cout << v.size() << endl;
  cout << "=============END TEST=============" << endl;
  return 0;
}
