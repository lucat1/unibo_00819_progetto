#ifndef TREEMAP_HPP
#define TREEMAP_HPP

#include "map.hpp"

namespace Nostd
{
    
    template<class K, class V>
    class TreeNode {
        public:
            K key;
            V value;
            TreeNode<K,V>* left;
            TreeNode<K,V>* right;

            TreeNode(K key, V value);
    };

    template<class K, class V>
    class Tree {
        public:
            Tree();
            // todo
            TreeNode<K,V>* root;
            void add(K key, V value);
    };
    
    template<class K, class V>
    class TreeMap : public Map<K,V> {
        private:
            Tree<K,V>* tree;
        
        public:

            TreeMap();

            void add(K key, V value) override;
            void remove(K key) override;

            V operator[](K key) override;
    };

} // namespace Nostd

#endif
