#ifndef __NOSTDMAP__
#define __NOSTDMAP__

#include <vector>

namespace Nostd
{
    template<typename K, typename V>
    class Map {
        public:

            virtual void add(K key, V value) = 0;
            virtual void remove(K key) = 0;
            virtual bool empty() = 0;
            virtual bool contains(K key) = 0;
            virtual std::vector<V>get_values() = 0; 

            virtual V operator[](K key) = 0;
    };
  


} // namespace nostd

#endif
