#include <iostream>
#include "tree_map.hpp"

using namespace std;

int main()
{
    cout << "=============MAP TEST=============" << endl;
    Nostd::TreeMap<int, int> ma;
    cout << "[] add" << endl;
    ma.add(2, 3);
    ma.add(4, 5);
    ma.add(1,23);
    cout << "[] operator []" << endl;
    cout << ma[4] << endl;
    cout << "[] remove" << endl;
    ma.remove(2);
    cout << "[] get values" << endl;
    auto v = ma.get_values();
    cout << v.size() << endl;
    for (auto &p : ma.get_values())
    {
        cout << p << endl;
    }
    cout << "=============END TEST=============" << endl;
    return 0;
}