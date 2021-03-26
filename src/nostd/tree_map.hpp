
#ifndef TREEMAP_HPP
#define TREEMAP_HPP

#include "map.hpp"
#include "vector.hpp"
#include <cassert>
#include <cstddef>
#include <exception>

#include <iostream>
using namespace std;

namespace Nostd {

template <class K, class V> class TreeNode {
public:
  K key;
  V value;
  TreeNode<K, V> *father;
  TreeNode<K, V> *left;
  TreeNode<K, V> *right;

  TreeNode(K key, V value, TreeNode<K, V> *f) {
    this->father = f;
    this->key = key;
    this->value = value;
  }

  bool operator==(TreeNode<K, V> other) { return other->key == this->key; }
};

template <class K, class V> class Tree {
public:
  Tree() {}

  ~Tree() { delete root; }

  TreeNode<K, V> *root;

  void add(K key, V value) {
    TreeNode<K, V> *p = nullptr;
    TreeNode<K, V> *t = this->root;
    while (t != nullptr) {
      p = t;
      if (key <= t->key)
        t = t->left;
      else
        t = t->right;
    }
    if (p == nullptr)
      this->root = new TreeNode<K, V>(key, value, nullptr);
    else if (key <= p->key)
      p->left = new TreeNode<K, V>(key, value, p);
    else
      p->right = new TreeNode<K, V>(key, value, p);
  }

  void remove(K key) {
    TreeNode<K, V> *ptr = this->root;
    while (ptr != nullptr) {
      if (ptr->key == key)
        break;
      if (key <= ptr->key)
        ptr = ptr->left;
      else
        ptr = ptr->right;
    }
    if (ptr == nullptr)
      return;
    // 1. Leaf
    if (ptr->left == nullptr && ptr->right == nullptr) {
      cout << "qua" << endl;
      ptr = nullptr;
      delete ptr;
    }
    // 2. Right is null
    else if (ptr->right == nullptr) {
      if (ptr->father->left == ptr)
        ptr->father->left = ptr->left;
      else
        ptr->father->right = ptr->left;
      delete ptr;
    }
    // 3. Left is null
    else if (ptr->left == nullptr) {
      if (ptr->father->right == ptr)
        ptr->father->right = ptr->right;
      else
        ptr->father->left = ptr->right;
      delete ptr;
    }
    // 4 nobody is null
    else if (ptr->left != nullptr && ptr->right != nullptr) {
      TreeNode<K, V> *tmp = get_predecessor(key);
      assert(tmp != nullptr);
      remove(tmp->key);
      ptr->key = tmp->key;
      ptr->value = tmp->value;
    }
  }

  TreeNode<K, V> *get_predecessor(K key) {
    TreeNode<K, V> *res = nullptr;
    TreeNode<K, V> *ptr = this->root;
    while (ptr != nullptr) {
      if (ptr->key > res->key) {
        res = ptr;
      }
      if (key <= ptr->key) {
        ptr = ptr->left;
      } else {
        ptr = ptr->right;
      }
    }
    return res;
  }

  K get(K key) {
    TreeNode<K, V> *ptr = this->root;

    while (ptr != nullptr && ptr->key != key) {
      if (ptr->key >= key) {
        ptr = ptr->left;
      } else {
        ptr = ptr->right;
      }
    }

    if (ptr == nullptr) {
      throw std::invalid_argument("Treemap: No value found for that key");
    }
    return ptr->value;
  }

  bool find(const K &key) {
    TreeNode<K, V> *ptr = this->root;

    while (ptr != nullptr && ptr->key != key) {
      if (ptr->key >= key) {
        ptr = ptr->left;
      } else {
        ptr = ptr->right;
      }
    }
    return ptr != nullptr;
  }

  Nostd::Vector<V> get_values() {
    Nostd::Vector<V> res;
    return get_elements(this->root);
  }

private:
  Nostd::Vector<V> get_elements(const TreeNode<K, V> *current) {
    Nostd::Vector<V> vec;
    if (current == nullptr)
      return vec;
    Nostd::Vector<V> lv = get_elements(current->left);
    vec.push_back(current->value);
    Nostd::Vector<V> rv = get_elements(current->right);
    for (size_t i = 0; i < lv.size(); i++)
      vec.push_back(lv[i]);
    for (size_t i = 0; i < rv.size(); i++)
      vec.push_back(rv[i]);
    return vec;
  }
};

template <class K, class V> class TreeMap : public virtual Map<K, V> {
private:
  Tree<K, V> *tree;

public:
  TreeMap() { this->tree = new Tree<K, V>(); }

  ~TreeMap() { delete tree; }

  void add(K key, V value) override { this->tree->add(key, value); }

  void remove(K key) override { this->tree->remove(key); }

  V operator[](K key) override { return this->tree->get(key); }

  bool empty() override { return this->tree == nullptr; }

  bool contains(K key) override { return this->tree->find(key); }

  Nostd::Vector<V> get_values() override { return this->tree->get_values(); }

  Nostd::Vector<Nostd::Pair<K, V>> as_vector() override {
    return Nostd::Vector<Nostd::Pair<K, V>>();
  }
};

} // namespace Nostd

#endif
