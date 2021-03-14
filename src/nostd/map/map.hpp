#ifndef __NOSTDMAP__
#define __NOSTDMAP__

namespace Nostd
{
    template<class K, class V>
    class Map {
        public:

            virtual void add(K key, V value);
            virtual void remove(K key);

            virtual V operator[](K key);
    };
  


} // namespace nostd

#endif
