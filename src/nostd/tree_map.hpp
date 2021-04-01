/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Mattia Girolimetto #977478
  04/01/2021

  tree_map.cpp: implementation of Nostd::TreeMap.
*/

#ifndef NOSTD_TREEMAP_HPP
#define NOSTD_TREEMAP_HPP

#include "map.hpp"
#include "vector.hpp"
#include <cassert>
#include <cstddef>
#include <cstdio>
#include <exception>

namespace Nostd {

/**

  TreeMap

  Built using an BST. Please refere to Nostd::Map for method's documentation

**/
template <class K, class V> class TreeMap : public virtual Map<K, V> {
private:
  class Tree {
  private:
    class TreeNode {
    public:
      K key;
      V value;
      TreeNode *parent = nullptr;
      TreeNode *left = nullptr;
      TreeNode *right = nullptr;
      explicit TreeNode(K key, V value, TreeNode *f) {
        this->parent = f;
        this->key = key;
        this->value = value;
      }

      bool operator==(TreeNode other) { return other->key == this->key; }
    };

    Nostd::Vector<V> get_elements(const TreeNode *current) {
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

    TreeNode *insert(TreeNode *node, K key, V value) {
      if (node == nullptr) {
        children++;
        return new TreeNode(key, value, nullptr);
      }
      if (key == node->key) {
        node->value = value;
      } else if (key <= node->key) {
        node->left = insert(node->left, key, value);
        node->left->parent = node;
        children++;
      } else {
        node->right = insert(node->right, key, value);
        node->right->parent = node;
        children++;
      }
      return node;
    }

    void remove_node(TreeNode *ptr) {
      if (ptr->parent == nullptr) // root
        root = nullptr;
      else {
        if (ptr->parent->left != nullptr && ptr->parent->left->key == ptr->key)
          ptr->parent->left = nullptr;
        else
          ptr->parent->right = nullptr;
      }
      delete ptr;
      children--;
    }

  public:
    size_t children;

    Tree() : children(0) {}

    ~Tree() { delete root; }

    TreeNode *root = nullptr;

    void insert(K key, V value) { this->root = insert(root, key, value); }

    void clear(TreeNode *root) {
      if (root == nullptr)
        return;
      remove_node(root->left);
      remove_node(root->right);
      remove_node(root);
    }

    // Remove an element from the tree
    void remove(K key) {
      TreeNode *ptr = this->root;
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
        remove_node(ptr);
      }
      // 2. Right is null
      else if (ptr->right == nullptr) {
        if (ptr->parent == nullptr)
          ptr = ptr->left;
        else if (ptr->parent->left == ptr)
          ptr->parent->left = ptr->left;
        else
          ptr->parent->right = ptr->left;
        remove_node(ptr);
      }
      // 3. Left is null
      else if (ptr->left == nullptr) {
        if (ptr->parent == nullptr)
          ptr = ptr->right;
        else if (ptr->parent->right == ptr)
          ptr->parent->right = ptr->right;
        else
          ptr->parent->left = ptr->right;
        remove_node(ptr);
      }
      // 4 nobody is null
      else if (ptr->left != nullptr && ptr->right != nullptr) {
        TreeNode *tmp = get_predecessor(key);
        remove(tmp->key);
        ptr->key = tmp->key;
        ptr->value = tmp->value;
      }
    }

    TreeNode *get_predecessor(K key) {
      TreeNode *res = nullptr;
      TreeNode *ptr = this->root;
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

    V &get(K key) {
      TreeNode *ptr = this->root;

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
      TreeNode *ptr = this->root;

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
  };

  Tree *tree;

public:
  TreeMap() {
    this->tree = new Tree();
    this->sz = 0;
  }

  ~TreeMap() { delete tree; }

  void put(K key, V value) override {
    this->tree->insert(key, value);
    this->sz++;
  }

  void remove(K key) override { this->tree->remove(key); }

  V &operator[](K key) override { return this->tree->get(key); }

  bool empty() override { return this->tree == nullptr; }

  bool contains(K key) override { return this->tree->find(key); }

  size_t size() override { return this->tree->children; }

  Nostd::Vector<V> get_values() override { return this->tree->get_values(); }

  void clear() override { this->tree->clear(this->tree->root); }

  Nostd::Vector<Nostd::Pair<K, V>> as_vector() override {
    return Nostd::Vector<Nostd::Pair<K, V>>();
  }
};

} // namespace Nostd

#endif
