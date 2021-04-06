/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Mattia Girolimetto #977478
  04/01/2021

  tree_map.cpp: implementation of Nostd::TreeMap built using an BST.
  Please refere to Nostd::Map for method's documentation.

  Warining: It does not allow duplicates
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

      explicit TreeNode(K key, V value, TreeNode *p, TreeNode *l, TreeNode *r) {
        this->parent = p;
        this->left = l;
        this->right = r;
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
      } else if (key < node->key) {
        node->left = insert(node->left, key, value);
        node->left->parent = node;
      } else {
        node->right = insert(node->right, key, value);
        node->right->parent = node;
      }
      return node;
    }

    // Does not care of the parent
    void remove_node(TreeNode *ptr) {
      if (ptr != nullptr) {
        delete ptr;
        children--;
      }
    }

    // Returns an in-order visit of a subtree
    void in_order(TreeNode *node, Nostd::Vector<Nostd::Pair<K, V>> &res) {
      if (node == nullptr)
        return;
      in_order(node->left, res);
      res.push_back(Pair<K, V>(node->key, node->value));
      in_order(node->right, res);
    }

  public:
    size_t children;

    Tree() : children(0) {}

    ~Tree() { delete root; }

    TreeNode *root = nullptr;

    void insert(K key, V value) { this->root = insert(root, key, value); }

    // Root's parent will have a "nodo penzolante"
    void clear(TreeNode *root) {
      if (root == nullptr)
        return;
      clear(root->left);
      clear(root->right);
      remove_node(root);
    }

    // Remove an element from the tree
    void remove(K key) {
      TreeNode *ptr = this->root;
      while (ptr != nullptr && ptr->key != key) {
        if (ptr->key >= key)
          ptr = ptr->left;
        else
          ptr = ptr->right;
      }
      // Empty tree/key not found
      if (ptr == nullptr) {
        throw std::invalid_argument("Treemap: No value found for the key " +
                                    std::to_string(key));
        return;
      }
      // 1. Leaf
      if (ptr->left == nullptr && ptr->right == nullptr) {
        if (ptr->parent->left != nullptr && ptr->parent->left == ptr)
          ptr->parent->left = nullptr;
        else
          ptr->parent->right = nullptr;
        remove_node(ptr);
        return;
      }
      // 2. One child null
      else if (ptr->left == nullptr || ptr->right == nullptr) {
        // if ptr is left child
        if (ptr->parent->left == ptr) {
          // Left is null
          if (ptr->left == nullptr && ptr->right != nullptr)
            ptr->parent->left = ptr->right;
          // Right is null
          if (ptr->right == nullptr && ptr->left != nullptr)
            ptr->parent->left = ptr->left;
          remove_node(ptr);
          return;
        }
        // if ptr is right child
        else {
          // left is null
          if (ptr->left == nullptr && ptr->right != nullptr)
            ptr->parent->right = ptr->right;
          // right is null
          if (ptr->right == nullptr && ptr->left != nullptr)
            ptr->parent->right = ptr->left;
          remove_node(ptr);
          return;
        }
      }

      // 3. Both children null
      else if (ptr->left != nullptr && ptr->right != nullptr) {
        // a. Find predecessor
        // b. Replace node to delete predecessor
        // c. Delete old predecessor
        TreeNode *pred = get_predecessor(key);
        K pkey = pred->key;
        V pvalue = pred->value;
        remove(pred->key);
        ptr->key = pkey;
        ptr->value = pvalue;
        return;
      }
    }

    // Return nullptr if there is no predecessor
    TreeNode *get_predecessor(K key) {
      TreeNode *res = nullptr;
      TreeNode *ptr = this->root;
      while (ptr != nullptr) {
        if (ptr->key < key && (res == nullptr || ptr->key > res->key)) {
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
        throw std::invalid_argument("Treemap: No value found for the key " +
                                    std::to_string(key));
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

    Nostd::Vector<Nostd::Pair<K, V>> as_vector() {
      Nostd::Vector<Nostd::Pair<K, V>> res;
      in_order(this->root, res);
      return res;
    }
  };

  Tree *tree;

public:
  TreeMap() { this->tree = new Tree(); }

  ~TreeMap() { delete tree; }

  void put(K key, V value) override { this->tree->insert(key, value); }

  void remove(K key) override { this->tree->remove(key); }

  V &operator[](K key) override { return this->tree->get(key); }

  const V &operator[](K key) const override { return this->tree->get(key); }

  bool empty() const override { return this->tree == nullptr; }

  bool contains(K key) const override { return this->tree->find(key); }

  size_t size() const override { return this->tree->children; }

  Nostd::Vector<V> get_values() const override {
    return this->tree->get_values();
  }

  void clear() override {
    this->tree->clear(this->tree->root);
    this->tree->root = nullptr;
  }

  Nostd::Vector<Nostd::Pair<K, V>> as_vector() const override {
    return this->tree->as_vector();
  }
};

} // namespace Nostd

#endif
