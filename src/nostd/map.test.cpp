#include "../util/test.hpp"
#include "map.hpp"
#include "tree_map.hpp"
#include "unordered_map.hpp"
#include <cassert>
#include <iostream>

using namespace std;
using namespace Nostd;

int main() {
  it("umap: put", {
    Nostd::UnorderedMap<int, int> um;
    um.put(2, 5);
    um.put(4, 10);
    um.put(1, 23);
    um.put(5, 111);
  });
  it("umap: operator []", {
    Nostd::UnorderedMap<int, int> um;
    um.put(2, 5);
    um[2] = 10;
    assert(um[2] == 10);
  });

  it("umap: get_values", {
    Nostd::UnorderedMap<int, int> um;
    um.put(2, 5);
    um.put(4, 25);
    auto v = um.get_values();
    assert(v.size() == 2);
  });

  it("umap contains", {
    Nostd::UnorderedMap<int, int> um;
    um.put(4, 5);
    assert(um.contains(4));
  });

  it("umap: remove", {
    Nostd::UnorderedMap<int, int> um;
    um.put(4, 5);
    um.put(10, 15);
    um.remove(4);
    assert(um.get_values().size() == 1);
  });

  // Treemap

  it("tmap: put", {
    Nostd::TreeMap<int, int> um;
    um.put(2, 5);
    um.put(4, 10);
    um.put(1, 23);
    um.put(5, 111);
  });
  it("tmap: operator []", {
    Nostd::TreeMap<int, int> um;
    um.put(2, 5);
    um[2] = 10;
    assert(um[2] == 10);
  });

  it("tmap: get_values", {
    Nostd::TreeMap<int, int> um;
    um.put(2, 5);
    um.put(4, 25);
    auto v = um.get_values();
    assert(v.size() == 2);
  });

  it("tmap: contains", {
    Nostd::TreeMap<int, int> um;
    um.put(4, 5);
    assert(um.contains(4));
  });

  it("tmap: remove", {
    Nostd::TreeMap<int, int> um;
    um.put(4, 5);
    um.put(14, 10);
    um.remove(4);
    cout << um.get_values().size() << endl;
    assert(um.get_values().size() == 1);
  });
  return 0;
}
