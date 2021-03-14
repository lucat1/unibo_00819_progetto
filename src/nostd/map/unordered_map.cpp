#include "unordered_map.hpp"

using namespace std;
using namespace Nostd;

template<typename K, typename V> 
UnorderedMap<K,V>::UnorderedMap(){
    data = vector<K, V>();
}

template<typename K, typename V> 
void UnorderedMap<K,V>::add(K key, V value){
    data[key] = value;
}

template<typename K, typename V> 
void UnorderedMap<K,V>::remove(K key){
    data.erase(key);
}


template<typename K, typename V> 
V UnorderedMap<K,V>::operator[](K key){
    return data[key];
}