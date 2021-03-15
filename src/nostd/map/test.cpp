#include <iostream>
#include "unordered_map.hpp"

using namespace std;

int main() {
    Nostd::UnorderedMap<int, int> ma;
    ma.add(2,3);
    ma.add(4,5);
    //cout << ma[4];
    cout << ma[1];

    return 0;
}