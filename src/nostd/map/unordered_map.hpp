#ifndef UNORDEREDMAP_HPP
#define UNORDEREDMAP_HPP

#include "map.hpp"
#include "../pair/pair.hpp"
#include <vector>
#include <exception>
#include <iostream>

namespace Nostd
{
    template <typename K, typename V>
    class UnorderedMap : public Map<K, V>
    {
    private:
        std::vector<Nostd::Pair<K, V>> data;

    public:
        UnorderedMap()
        {
            data = std::vector<Nostd::Pair<K, V>>();
        }

        void add(K key, V value) override
        {
            for (auto &x : data)
            {
                if (x.first == key)
                {
                    x.second = value;
                    return;
                }
            }
            data.push_back({key, value});
        }

        void remove(K key) override
        {
            for (size_t i = 0; i < this->data.size(); i++)
                if (data[i].first == key)
                {
                    data.erase(this->data.begin() + i);
                    return;
                }
        }

        bool empty() override
        {
            return this->data.empty();
        }

        bool contains(K key) override
        {
            // todo: waiting for nostd::vector implementation
            for (auto &x : this->data)
                if (key == x.first)
                    return true;
            return false;
        }

        std::vector<V> get_values() override
        {
            std::vector<V> res;
            for (auto &x : this->data)
                res.push_back(x.second);
            return res;
        }

        std::vector<Nostd::Pair<K, V>> as_vector() override
        {
            return this->data;
        }

        V operator[](K key) override
        {
            for (auto &x : this->data)
                if (x.first == key)
                    return x.second;
            throw std::invalid_argument("UnorderedMap: No value found for that key");
        }
    };

} // namespace Nostd
#endif