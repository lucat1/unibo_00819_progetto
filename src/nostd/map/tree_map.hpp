
#ifndef TREEMAP_HPP
#define TREEMAP_HPP

#include "map.hpp"

namespace Nostd
{

    template <class K, class V>
    class TreeNode
    {
    public:
        K key;
        V value;
        TreeNode<K, V> *left;
        TreeNode<K, V> *right;

        TreeNode(K key, V value)
        {
            this->key = key;
            this->value = value;
        }
    };

    template <class K, class V>
    class Tree
    {
    public:
        Tree(){}
        // todo
        TreeNode<K, V> *root;

        void add(K key, V value)
        {
            TreeNode<K, V> *p = nullptr;
            TreeNode<K, V> *t = this->root;
            while (t != nullptr)
            {
                p = t;
                if (key <= t->key)
                    t = t->left;
                else
                    t = t->right;
            }
            if (p == nullptr)
                this->root = new TreeNode<K, V>(key, value);
            else if (key <= p->key)
                p->left = new TreeNode<K, V>(key, value);
            else
                p->right = new TreeNode<K, V>(key, value);
        }

        K get(K key)
        {
            TreeNode<K, V> *ptr = this->root;

            while (ptr != nullptr && ptr->key != key)
            {
                if (ptr->key >= key)
                {
                    ptr = ptr->left;
                }
                else
                {
                    ptr = ptr->right;
                }
            }

            if (ptr == nullptr)
            {
                throw std::invalid_argument("Treemap: No value found for that key");
            }
            return ptr->value;
        }

        bool find(const K &key)
        {
            TreeNode<K, V> *ptr = this->root;

            while (ptr != nullptr && ptr->key != key)
            {
                if (ptr->key >= key)
                {
                    ptr = ptr->left;
                }
                else
                {
                    ptr = ptr->right;
                }
            }
            return ptr != nullptr;
        }

        std::vector<V> get_values()
        {
            std::vector<V> res;
            return get_elements(this->root);
            
        }

    private:
        std::vector<V> get_elements(const TreeNode<K, V> *current)
        {
             std::vector<V> vec;
            if (current == nullptr)
                return vec;
            std::vector<V> lv = get_elements(current->left);
            vec.push_back(current->value);
            std::vector<V> rv = get_elements(current->right);
            for (auto &x : lv)
                vec.push_back(x);
            for (auto x : rv)
                vec.push_back(x);
            return vec;
        }
    };

    template <class K, class V>
    class TreeMap : public virtual Map<K, V>
    {
    private:
        Tree<K, V> *tree;

    public:
        TreeMap()
        {
            this->tree = new Tree<K, V>();
        }

        void add(K key, V value) override
        {
            this->tree->add(key, value);
        }

        void remove(K key) override {

        }

        V operator[](K key) override
        {
            return this->tree->get(key);
        }

        bool empty() override
        {
            return this->tree == nullptr;
        }

        bool contains(K key) override
        {
            return this->tree->find(key);
        }

        std::vector<V> get_values() override {
            return this->tree->get_values();
        }

        std::vector<Nostd::Pair<K, V>> as_vector() {
             return  std::vector<Nostd::Pair<K, V>>();
         }

    };

} // namespace Nostd

#endif
