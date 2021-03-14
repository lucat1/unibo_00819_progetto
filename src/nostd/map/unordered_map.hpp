#ifndef UNORDEREDMAP_HPP
#define UNORDEREDMAP_HPP

#include "map.hpp"
#include <vector>
#include <algorithm>

namespace Nostd
{
    template<class K, class V>
    class UnorderedMap : public Map<K,V> {
        private:
            std::vector<std::pair<K,V>> data;
        
        public:

            UnorderedMap();

            void add(K key, V value) override;
            void remove(K key) override;

            V operator[](K key) override;
    };

} // namespace Nostd


#endif