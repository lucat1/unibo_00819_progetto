#ifndef __NOSTDMAP__
#define __NOSTDMAP__

#include <vector>
#include "../pair/pair.hpp"

namespace Nostd
{
    template <typename K, typename V>
    class Map
    {
    public:
        virtual void add(K key, V value) = 0;
        virtual void remove(K key) = 0;
        virtual bool empty() = 0;
        virtual bool contains(K key) = 0;
        virtual std::vector<V> get_values() = 0;
        virtual std::vector<Nostd::Pair<K, V>> as_vector() = 0;

        virtual V operator[](K key) = 0;
    };

} // namespace nostd

#endif
