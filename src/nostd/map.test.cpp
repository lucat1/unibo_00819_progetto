#include "../util/test.hpp"
#include "map.hpp"
#include "tree_map.hpp"
#include "unordered_map.hpp"
#include <iostream>

using namespace std;
using namespace Nostd;

int main() {
  it("umap: add", {
    Nostd::UnorderedMap<int, int> um;
    um.add(2, 5);
    um.add(4, 10);
    um.add(1, 23);
    um.add(5, 111);
  });
  it("umap: operator []", {
    Nostd::UnorderedMap<int, int> um;
    um.add(2, 5);
    um[2] = 10;
    assert(um[2] == 10);
  });

  it("umap: get_values", {
    Nostd::UnorderedMap<int, int> um;
    um.add(2, 5);
    um.add(4, 25);
    auto v = um.get_values();
    assert(v.size() == 2);
  });

  it("umap: remove", {
    Nostd::UnorderedMap<int, int> um;
    um.add(4, 5);
    um.add(10, 15);
    um.remove(4);
    assert(um.get_values().size() == 1);
  });

  cout << "=============TREEMAP TEST=============" << endl;
  Nostd::TreeMap<int, int> ma;
  cout << "[] add" << endl;
  ma.add(2, 3);
  ma.add(4, 5);
  ma.add(1, 23);
  cout << "[] operator []" << endl;
  cout << ma[4] << endl;
  ma[4] = 10;
  cout << ma[4] << endl;
  cout << "[] get values" << endl;
  auto v = ma.get_values();
  cout << v.size() << endl;
  cout << "[] remove" << endl;
  ma.remove(1);
  cout << "[] get values" << endl;
  auto vv = ma.get_values();
  cout << vv.size() << endl;
  cout << "=============END TEST=============" << endl;
  return 0;
}
