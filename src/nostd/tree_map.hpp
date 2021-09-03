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
#include <exception>
#include <iterator>

namespace Nostd {

/*
  The TreeMap class is an interface between Nostd::Map methods and a tree.
 */
template <class K, class V> class TreeMap : public virtual Map<K, V> {
private:
  /*
    Actual Tree implemenentation
  */
  class Tree {
  private:
    /*
      Core data structure of Treemap. It represents the tree's binary node.
      To keep things simple we save a reference to the parent (nullptr if it's
      root) along with references to both left and right children
    */
    struct TreeNode {
      Nostd::Pair<const K, V> *data;
      TreeNode *parent = nullptr;
      TreeNode *left = nullptr;
      TreeNode *right = nullptr;

      // Constructors
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

      // Getters and setters
      const K get_key(void) const noexcept { return this->data->first; }
      V get_value(void) const noexcept { return this->data->second; }

      void set_value(V v) noexcept { this->data->second = v; }

      bool operator==(const TreeNode &other) noexcept {
        return other->data->first == this->get_key();
      }
    };

    /*
      Given a TreeNode* it returns all the values of the tree in pre-order
     */
    Nostd::Vector<V> get_elements(const TreeNode *current) const noexcept {
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

    /*
      Insert a new key with its value at the right position inside a TreeNode.
      The position is determined using BST logic.
     */
    TreeNode *insert(TreeNode *node, K key, V value) noexcept {
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

    /*
      Remove a node and clear its reference.
      Note: Does not care of the parent
    */
    void remove_node(TreeNode *ptr) noexcept {
      if (ptr != nullptr) {
        delete ptr;
        children--;
      }
    }

    /*
      Returns an in-order visit of a subtree
    */
    void
    in_order(const TreeNode *node,
             Nostd::Vector<Nostd::Pair<const K, V> *> &res) const noexcept {
      if (node == nullptr)
        return;
      in_order(node->left, res);
      res.push_back(
          new Nostd::Pair<const K, V>(node->data->first, node->data->second));
      in_order(node->right, res);
    }

  public:
    // The number of nodes in the tree
    size_t children;

    // Root node
    TreeNode *root = nullptr;

    Tree() : children(0) {}

    ~Tree() { clear(root); }

    /*
      Insert a new key and value pair inside the tree
     */
    void insert(K key, V value) noexcept {
      this->root = insert(root, key, value);
    }

    /*
      Remove a TreeNode and its subtrees
    */
    void clear(TreeNode *r) noexcept {
      if (r == nullptr)
        return;
      clear(r->left);
      clear(r->right);
      remove_node(r);
    }

    /*
      Remove an element from the tree
    */
    void remove(const K key) {
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
        delete ptr->data;
        ptr->data = p_data;
        return;
      }
    }

    /*
      Returns the root of the TreeNode* given in input
     */
    static TreeNode *get_root(TreeNode *node) noexcept {
      if (node == nullptr)
        return nullptr;
      while (node->parent != nullptr)
        node = node->parent;
      return node;
    }

    /*
      Given a root TreeNode reference and a key returns the TreeNode*
      predecessor of the key. A predecessor of a TreeNode is the node which
      value is the greatest between nodes with value that are smaller than the
      one paired with the key of the node given in input. For example: if 1, 2,
      3, 4 are values inside a Tree, "3" predecessor is "2", and "4" predecessor
      is "3".
      Note: Returns nullptr if there is no predecessor
     */
    static TreeNode *get_predecessor(TreeNode *root, const K &key) noexcept {
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

    /*
      Given a root TreeNode reference and a key returns the TreeNode*
      successor of the key. A successor of a TreeNode is the node which
      value is the smallest between nodes with value that are greater than the
      one paired with the key of the node given in input. For example: if 1, 2,
      3, 4 are values inside a Tree, "3" sucessor is "4", and "2" sucessor
      is "3".
      Note: Returns nullptr if there is no predecessor
     */
    static TreeNode *get_successor(TreeNode *root, const K &key) noexcept {
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

    /*
      Returns the value paired with the key given in input
     */
    V &get(const K &key) const {
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

    /*
      Checks wheter a key is present inside the tree
     */
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

    /*
      Returns all values inside the tree using a Nostd::Vector<V>
     */
    Nostd::Vector<V> get_values(void) const noexcept {
      return get_elements(this->root);
    }

    /*
      Returns a Nostd::Vector<Nostd::Pair<const K, V>> representation of the
      Tree
     */
    Nostd::Vector<Nostd::Pair<const K, V> *> as_vector() const noexcept {
      Nostd::Vector<Nostd::Pair<const K, V> *> res;
      in_order(this->root, res);
      return res;
    }

    /*
     Returns the node with the smallest key
     */
    TreeNode *min() const noexcept {
      TreeNode *ptr = root;
      while (ptr->left != nullptr)
        ptr = ptr->left;
      return ptr;
    }

    /*
      Returns the node with the greatest key
    */
    TreeNode *max() const noexcept {
      TreeNode *ptr = root;
      while (ptr->right != nullptr)
        ptr = ptr->right;
      return ptr;
    }

    /*
       Built following guidelines from:
       https://en.cppreference.com/w/cpp/iterator/iterator
    */
    class Iterator : public std::iterator<std::forward_iterator_tag,
                                          Nostd::Pair<const K, V>, long,
                                          TreeNode *, TreeNode> {
    private:
      TreeNode *ptr;

    public:
      Iterator(TreeNode *node) noexcept : ptr(node) {}

      Nostd::Pair<const K, V> begin() const noexcept {
        TreeNode *t = min();
        return t->data;
      }

      Nostd::Pair<const K, V> end(void) const noexcept { return nullptr; }

      Iterator &operator=(TreeNode *node) noexcept {
        this->ptr = node;
        return *this;
      }

      Iterator &operator++(void) noexcept {
        if (ptr) {
          TreeNode *r = get_root(ptr);
          ptr = get_successor(r, ptr->get_key());
        }
        return *this;
      }

      Iterator operator++(int) noexcept {
        Iterator retVal = *this;
        ++(*this);
        return retVal;
      }

      bool operator!=(Iterator &iterator) noexcept {
        return this->ptr != iterator.ptr;
      }

      Nostd::Pair<const K, V> *operator*() noexcept { return this->ptr->data; }

      bool operator==(Iterator it) noexcept { return this->ptr == it.ptr; }
    };
  };

  Tree *tree;

public:
  using iterator = typename Tree::Iterator;
  using const_iterator = const iterator;

  TreeMap() { this->tree = new Tree(); }

  ~TreeMap() { delete tree; }

  /*
    Insert a key and its value inside the tree
   */
  void put(K key, V value) noexcept override { this->tree->insert(key, value); }

  /*
    Remove a key and its value fron the tree
   */
  void remove(K key) override { this->tree->remove(key); }

  /*
    Access a value from its key
   */
  V &operator[](const K &key) override { return this->tree->get(key); }

  const V &operator[](const K &key) const override {
    return this->tree->get(key);
  }

  /*
    Checks wheter there are keys inside the tree
   */
  bool empty(void) const noexcept override { return this->tree == nullptr; }

  /*
    Checks wheter the tree contains a key given in input
   */
  bool contains(const K &key) const noexcept override {
    return this->tree->find(key);
  }

  /*
    Returns the number of elements inside the tree
   */
  size_t size(void) const noexcept override { return this->tree->children; }

  Nostd::Vector<V> get_values(void) const noexcept override {
    return this->tree->get_values();
  }

  /*
    Delete all keys and values from the tree
   */
  void clear(void) noexcept override {
    this->tree->clear(this->tree->root);
    this->tree->root = nullptr;
  }

  /*
    Returns a Nostd::Vector<Nostd::Pair<const K, V>*> representation of the
    TreeMap
   */
  Nostd::Vector<Nostd::Pair<const K, V> *>
  as_vector(void) const noexcept override {
    return this->tree->as_vector();
  }

  // Iterator methods
  iterator begin(void) noexcept { return iterator(this->tree->min()); }

  iterator end(void) noexcept { return iterator(this->tree->max()->right); }

  const_iterator cbegin(void) const noexcept {
    return iterator(this->tree->min());
  }

  const_iterator cend(void) const noexcept {
    return iterator(this->tree->max()->right);
  }
};

} // namespace Nostd

#endif
