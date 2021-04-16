/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Mattia Girolimetto #977478
  04/01/2021

  tree_map.cpp: implementation of Nostd::TreeMap built using an BST.
  In this file you'll find the implementation of:
    - struct TreeNode: The BST's kernel.
    - class Tree: A class delegate used by TreeMap to use the BST.
    - class Tree::Iterator: A foward-iterator for Tree class.
    - class TreeMap<K, V>: Extending Nostd::Map this class provides all the
  methods for the end user.

  Please refere to Nostd::Map for method's documentation.

  Warning: Key types must have '<', '>', '==' and '!=' operator defined
  Warining: It does not allow duplicates

  Notes about Tree::Iterator:
  Note that the STL implementation of std::map (on which Nostd::TreeMap is based
  upon) uses a bidirectional-iterator. This implementation is complex in terms
  of time. Going foward to the next element in the worst case has a cost of O(n)
  where n is the number of elements. This could be avoided using a Red-Black
  Tree instead of the Binary Search Tree. This choice was made to keep the
  complexity of the class low.
*/

#ifndef NOSTD_TREEMAP_HPP
#define NOSTD_TREEMAP_HPP

#include "map.hpp"
#include "vector.hpp"
#include <cassert>
#include <cstddef>
#include <cstdio>
#include <exception>
#include <iterator>

namespace Nostd {

template <class K, class V> class TreeMap : public virtual Map<K, V> {
private:
  class Tree {
  private:
    struct TreeNode {
      Nostd::Pair<const K, V> *data;
      TreeNode *parent = nullptr;
      TreeNode *left = nullptr;
      TreeNode *right = nullptr;

      explicit TreeNode(const K key, V value, TreeNode *f) {
        this->data = new Nostd::Pair<const K, V>(key, value);
        this->parent = f;
      }

      explicit TreeNode(const K key, V value, TreeNode *p, TreeNode *l,
                        TreeNode *r) {
        this->parent = p;
        this->left = l;
        this->right = r;
        this->data = Nostd::Pair<const K, V>(key, value);
      }

      ~TreeNode() { delete data; }

      const K get_key() { return this->data->first; }
      V get_value() const { return this->data->second; }

      void set_value(V v) { this->data->second = v; }

      bool operator==(TreeNode other) {
        return other->data->first == this->get_key();
      }
    };

    Nostd::Vector<V> get_elements(const TreeNode *current) const {
      Nostd::Vector<V> vec;
      if (current == nullptr)
        return vec;
      Nostd::Vector<V> lv = get_elements(current->left);
      vec.push_back(current->data->second);
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
      if (key == node->data->first) {
        node->set_value(value);
      } else if (key < node->data->first) {
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
    void in_order(TreeNode *node,
                  Nostd::Vector<Nostd::Pair<const K, V> *> &res) {
      if (node == nullptr)
        return;
      in_order(node->left, res);
      res.push_back(
          new Nostd::Pair<const K, V>(node->data->first, node->data->second));
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
      while (ptr != nullptr && ptr->data->first != key) {
        if (ptr->data->first >= key)
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
        TreeNode *pred = get_predecessor(this->root, key);
        Nostd::Pair<const K, V> *p_data = pred->data;
        remove(pred->data->first);
        ptr->data = p_data;
        return;
      }
    }

    static TreeNode *get_root(TreeNode *node) {
      if (node == nullptr)
        return nullptr;
      while (node->parent != nullptr)
        node = node->parent;
      return node;
    }

    // Return nullptr if there is no predecessor
    static TreeNode *get_predecessor(TreeNode *root, K key) {
      TreeNode *res = nullptr;
      TreeNode *ptr = root;
      while (ptr != nullptr) {
        if (ptr->data->first < key &&
            (res == nullptr || ptr->data->first > res->get_key())) {
          res = ptr;
        }
        if (key <= ptr->data->first) {
          ptr = ptr->left;
        } else {
          ptr = ptr->right;
        }
      }
      return res;
    }

    // Return nullptr if there is no successor
    static TreeNode *get_successor(TreeNode *root, K key) {
      TreeNode *res = nullptr;
      TreeNode *ptr = root;
      while (ptr != nullptr) {
        if (ptr->data->first > key &&
            (res == nullptr || ptr->data->first < res->get_key())) {
          res = ptr;
        }
        if (key < ptr->data->first) {
          ptr = ptr->left;
        } else {
          ptr = ptr->right;
        }
      }
      return res;
    }

    V &get(K key) const {
      TreeNode *ptr = this->root;

      while (ptr != nullptr && ptr->data->first != key) {
        if (ptr->data->first >= key) {
          ptr = ptr->left;
        } else {
          ptr = ptr->right;
        }
      }

      if (ptr == nullptr) {
        throw std::invalid_argument("Treemap: No value found for the key " +
                                    std::to_string(key));
      }
      return ptr->data->second;
    }

    bool find(const K &key) {
      TreeNode *ptr = this->root;

      while (ptr != nullptr && ptr->data->first != key) {
        if (ptr->data->first >= key) {
          ptr = ptr->left;
        } else {
          ptr = ptr->right;
        }
      }
      return ptr != nullptr;
    }

    Nostd::Vector<V> get_values() { return get_elements(this->root); }

    Nostd::Vector<Nostd::Pair<const K, V> *> as_vector() {
      Nostd::Vector<Nostd::Pair<const K, V> *> res;
      in_order(this->root, res);
      return res;
    }

    // Returns the node with the smallest key
    TreeNode *min() const noexcept {
      TreeNode *ptr = root;
      while (ptr->left)
        ptr = ptr->left;
      return ptr;
    }

    // Returns the node with the greatest key
    TreeNode *max() const noexcept {
      TreeNode *ptr = root;
      while (ptr->right != nullptr)
        ptr = ptr->right;
      return ptr;
    }

    /* Built following guidelines from:
       https://en.cppreference.com/w/cpp/iterator/iterator
    */
    class Iterator : public std::iterator<std::forward_iterator_tag,
                                          Nostd::Pair<const K, V>, long,
                                          TreeNode *, TreeNode> {
    private:
      TreeNode *ptr;

    public:
      Iterator(TreeNode *node) noexcept : ptr(node) {}

      Nostd::Pair<const K, V> begin() noexcept {
        TreeNode *t = min();
        return t->data;
      }

      Nostd::Pair<const K, V> end() noexcept { return nullptr; }

      Iterator &operator=(TreeNode *node) {
        this->ptr = node;
        return *this;
      }

      Iterator &operator++() {
        if (ptr) {
          TreeNode *r = get_root(ptr);
          ptr = get_successor(r, ptr->get_key());
        }
        return *this;
      }

      Iterator operator++(int) {
        Iterator retVal = *this;
        ++(*this);
        return retVal;
      }

      bool operator!=(Iterator &iterator) { return this->ptr != iterator.ptr; }

      Nostd::Pair<const K, V> *operator*() { return this->ptr->data; }

      bool operator==(Iterator it) { return this->ptr == it.ptr; }
    };
  };

  Tree *tree;

public:
  using Iterator = typename Tree::Iterator;
  using ConstIterator = const Iterator;

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

  Nostd::Vector<Nostd::Pair<const K, V> *> as_vector() const override {
    return this->tree->as_vector();
  }

  Iterator begin() { return Iterator(this->tree->min()); }

  Iterator end() { return Iterator(this->tree->max()->right); }

  ConstIterator cbegin() const { return Iterator(this->tree->min()); }

  ConstIterator cend() const { return Iterator(this->tree->max()->right); }
};

} // namespace Nostd

#endif
