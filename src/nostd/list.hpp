/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Andreea Scrob #989372
  03/24/2021

  list.hpp: implementation of Nostd::List.
*/
#ifndef NOSTD_LIST_HPP
#define NOSTD_LIST_HPP

#include <iterator>
#include <stddef.h>
#include <stdexcept>

namespace Nostd {
//
// Lists are sequence containers that allow constant time insert and erase
// operations anywhere within the sequence, and iteration in both directions.
template <typename V> class List {
public:
  struct Item {
    V val;
    Item *next, *prev;
    List<V> *list;

    Item(List<V> *list, Item *prev, Item *next = nullptr, V value = V())
        : val(value), next(next), prev(prev), list(list) {}
  };

  class const_iterator;
  struct iterator : public std::iterator<std::bidirectional_iterator_tag, V> {
    Item *item = nullptr;
    bool end = true;

    iterator() {}
    iterator(const iterator &it) = default;
    iterator &operator=(const iterator &it) = default;

    bool operator==(iterator it) const {
      if (end && it.end)
        return true;
      return item == it.item && end == it.end;
    }

    bool operator!=(iterator it) const { return !(*this == it); }

    V &operator*() { return item->val; }
    V *operator->() { return &item->val; }

    iterator &operator++() {
      if (!end) {
        if (item->next)
          item = item->next;
        else
          end = true;
      }
      return *this;
    }

    iterator operator++(int) {
      iterator backup = *this;
      ++*this;
      return backup;
    }

    iterator &operator--() {
      if (end)
        end = false;
      else if (item->prev)
        item = item->prev;
      return *this;
    }

    iterator operator--(int) {
      iterator backup = *this;
      --*this;
      return backup;
    }

    operator const_iterator() const {
      const_iterator it;
      it.item = iterator::item;
      it.end = iterator::end;
      return it;
    }
  };

  using reverse_iterator = std::reverse_iterator<iterator>;

  class const_iterator : public iterator {
  public:
    const V &operator*() { return iterator::operator*(); }
    const V *operator->() { return iterator::operator->(); }
  };

  using const_reverse_iterator = std::reverse_iterator<const_iterator>;

protected:
  size_t sz;
  Item *head, *tail;
  struct Iterator {};

public:
  // Costructs a empty list, without elements.
  List() {
    sz = 0;
    head = nullptr;
    tail = nullptr;
  }

  // It is a costructor that creates a list with width "size".
  List(size_t size) {
    sz = size;
    for (size_t i = 0; i < sz; i++) {
      Item *x = new Item(this, tail);
      if (i == 0)
        head = x;
      if (tail != nullptr)
        tail->next = x;
      tail = x;
    }
  }

  // It is a costructor that creates a list with size elements.
  List(size_t size, V ele) {
    sz = size;
    for (size_t i = 0; i < sz; i++) {
      Item *x = new Item(this, tail, nullptr, ele);
      if (i == 0)
        head = x;
      if (tail != nullptr)
        tail->next = x;
      tail = x;
    }
  }

  // Constructs a new list by moving all items of another list. Leaves the
  // previous list in an undefined state.
  List(List &&list) {
    head = tail = nullptr;
    sz = 0;
    *this = list;
  }

  List &operator=(List &&l) {
    erase(begin(), end());
    sz = l.sz;
    head = l.head;
    tail = l.tail;
    l.head = nullptr;
    l.tail = nullptr;

    for (Item *p = head; p != nullptr; p = p->next)
      p->list = this;

    return *this;
  }

  // Constructs a new list by copying all items from another list.
  List(const List &l) {
    sz = 0;
    head = tail = nullptr;
    *this = l;
  }

  List &operator=(const List &l) {
    erase(begin(), end());
    sz = l.sz;
    Item *prev = nullptr;
    for (Item *p = l.head; p != nullptr; p = p->next) {
      Item *x = new Item(*p);
      x->list = this;
      x->prev = prev;
      if (prev == nullptr)
        head = x;
      else
        x->prev->next = x;
      if (p == l.tail) {
        tail = x;
        x->next = nullptr;
      }
      prev = x;
    }
    return *this;
  }

  // Returns whether the list container is empty
  bool empty() const { return sz == 0; }
  // Returns the number of elements in the list container
  size_t size() const { return sz; }

  // Returns a reference to the first element in the list container
  V &front() { return head->val; }
  // Returns a reference to the last element in the list container.
  V &back() { return tail->val; }

  // Inserts a new element at the beginning of the list, right before its
  // current first element.
  void push_front(V ele) {
    Item *x = new Item(this, nullptr, head, ele);
    if (head != nullptr)
      head->prev = x;
    head = x;

    if (tail == nullptr)
      tail = x;
    sz++;
  }

  // Adds a new element at the end of the list container, after its current
  // last element.
  void push_back(V ele) {
    Item *x = new Item(this, tail, nullptr, ele);
    if (tail == nullptr)
      head = x;
    else
      tail->next = x;
    tail = x;
    sz++;
  }

  // Removes from the list container either  a
  // range of elements ([first,last)).
  // This effectively reduces the container size by the number of elements
  // removed, which are destroyed.
  iterator erase(iterator first, iterator last) {
    if (first == end())
      return first;

    if (first == begin())
      head = last == end() ? nullptr : last.item;
    else
      first.item->prev->next = last == end() ? nullptr : last.item;

    if (last == end())
      tail = first.item->prev;
    else
      last.item->prev = first.item->prev;

    for (iterator p = first; p != last;) {
      Item *del = p.item;
      ++p;
      delete del;
      sz--;
    }
    return last;
  }

  // Removes the first element in the list container, effectively reducing its
  // size by one.
  void pop_front() {
    if (!empty())
      erase(begin(), std::next(begin()));
  }

  // Removes the last element in the list container, effectively reducing the
  // container size by one.
  void pop_back() {
    if (!empty())
      erase(std::prev(end()), end());
  }

  // Resizes the container so that it contains n elements.
  // If n is smaller than the current container size, the content is reduced
  // to its first n elements, removing those beyond (and destroying them). If
  // n is greater than the current container size, the content is expanded by
  // inserting at the end as many elements as needed to reach a size of n. If
  // val is specified, the new elements are initialized as copies of val,
  // otherwise, they are value-initialized.
  void resize(size_t n, V val = V{}) {
    if (n > sz) {
      List l(n - sz, val);
      splice(end(), l);
    } else if (n < sz) {
      iterator fird = begin();

      for (size_t i = 0; i < n; i++)
        ++fird;
      erase(fird, end());
    }
  }

  // Transfers elements from l into the container, inserting them at
  // position(pos).This effectively inserts those elements into the container
  // and removes them from l, altering the sizes of both containers. The
  // operation does not involve the construction or destruction of any
  // element.
  void splice(iterator pos, List &l) {
    for (Item *p = l.head; p != nullptr; p = p->next)
      p->list = this;

    if (pos.item == head)
      head = l.head;
    else {
      pos.item->prev->next = l.head;
      l.head->prev = pos.item->prev;
    }

    if (pos.item == nullptr)
      tail = l.tail;
    else {
      l.tail->next = pos.item;
      pos.item->prev = l.tail;
    }
    sz += l.sz;
    l.sz = 0;
    l.head = nullptr;
    l.tail = nullptr;
  }

  // The container is extended by inserting new elements before the
  // element at the specified position.
  iterator insert(const_iterator position, V ele) {
    if (position == end())
      push_back(ele);
    else {
      sz++;
      Item *x = new Item(this, position.item->prev, position.item, ele);
      if (position == begin())
        head = x;
      else
        position.item->prev->next = x;
      position.item->prev = x;
    }
    return --position;
  }

  // Removes from the container all the elements that compare equal to ele.
  // This calls the destructor of these objects and reduces the container size
  // by the number of elements removed. inefficient implementation
  void remove(V ele) {
    for (iterator p = begin(); p != end();)
      if (p.item->val == ele) {
        iterator q = p;
        ++q;
        p = erase(p, q);
      } else
        ++p;
  }

  iterator begin() {
    iterator p;
    p.item = head;
    p.end = empty();
    return p;
  }

  const_iterator begin() const {
    iterator p;
    p.item = head;
    p.end = empty();
    return p;
  }

  iterator end() {
    iterator p;
    p.item = tail;
    p.end = true;
    return p;
  }

  const_iterator end() const {
    iterator p;
    p.item = tail;
    p.end = true;
    return p;
  }

  reverse_iterator rbegin() { return reverse_iterator(end()); }

  reverse_iterator rend() { return reverse_iterator(begin()); }

  const_iterator cbegin() const { return begin(); }

  const_iterator cend() const { return end(); }

  const_reverse_iterator crbegin() const {
    return const_reverse_iterator(end());
  }

  const_reverse_iterator crend() const { return const_reverse_iterator(end()); }
};

} // namespace Nostd

#endif
