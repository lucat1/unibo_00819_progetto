#ifndef NOSTD_LIST_HPP
#define NOSTD_LIST_HPP

#include <stddef.h>
#include <stdexcept>

namespace Nostd {
// Lists are sequence containers that allow constant time insert and erase
// operations anywhere within the sequence, and iteration in both directions.
template <typename V> class List {
protected:
  struct Item {
    V val;
    Item *next, *prev;
  };
  size_t sz;
  Item *head, *tail;

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
      Item *x = new Item;
      x->next = nullptr;
      x->prev = tail;
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
      Item *x = new Item;
      x->val = ele;
      x->next = nullptr;
      x->prev = tail;
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
  List &operator=(List &list) {
    erase(head, nullptr);
    sz = list.sz;
    head = list.head;
    tail = list.tail;
    list.head = nullptr;
    list.tail = nullptr;
    return *this;
  }
  // Constructs a new list by copying all items from another list.
  List(const List &list) {
    head = tail = nullptr;
    sz = 0;
    *this = list;
  }
  List &operator=(const List &list) {
    erase(head, nullptr);
    sz = list.sz;
    Item *prev = nullptr;

    for (Item *it = list.head; it != nullptr; it = it->next) {
      Item *x = new Item;
      x->val = it->val;

      if (prev == nullptr)
        head = x;
      prev = x;
    }

    tail = prev;
    tail->next = nullptr;
    return *this;
  }

  // Returns whether the list container is empty
  bool empty() { return sz == 0; }
  // Returns the number of elements in the list container
  size_t size() { return sz; }

  // Returns a reference to the first element in the list container
  V &front() { return head->val; }
  // Returns a reference to the last element in the list container.
  V &back() { return tail->val; }

  // Inserts a new element at the beginning of the list, right before its
  // current first element.
  void push_front(V ele) {
    Item *x = new Item;
    x->val = ele;
    x->next = head;
    x->prev = nullptr;

    if (head != nullptr)
      head->prev = x;
    head = x;

    if (tail == nullptr)
      tail = x;
    sz++;
  }
  // Adds a new element at the end of the list container, after its current last
  // element.
  void push_back(V ele) {
    Item *x = new Item;
    x->val = ele;
    x->next = nullptr;
    x->prev = tail;

    if (tail == nullptr)
      head = x;
    else
      tail->next = x;
    tail = x;
    sz++;
  }
  // Removes from the list container either a single element (position) or a
  // range of elements ([first,last)).
  // This effectively reduces the container size by the number of elements
  // removed, which are destroyed.
  Item *erase(Item *first, Item *last) {
    if (first == nullptr)
      return nullptr;

    if (head == first)
      head = last;
    else
      first->prev->next = last;

    if (last != nullptr)
      last->prev = first->prev;
    else
      tail = first->prev;

    for (Item *p = first; p != last;) {
      Item *del = p;
      p = p->next;
      delete del;
      sz--;
    }
    return last;
  }
  // Removes the first element in the list container, effectively reducing its
  // size by one.
  void pop_front() {
    if (head != nullptr)
      erase(head, head->next);
  }
  // Removes the last element in the list container, effectively reducing the
  // container size by one.
  void pop_back() { erase(tail, nullptr); }
  // Resizes the container so that it contains n elements.
  // If n is smaller than the current container size, the content is reduced to
  // its first n elements, removing those beyond (and destroying them). If n is
  // greater than the current container size, the content is expanded by
  // inserting at the end as many elements as needed to reach a size of n. If
  // val is specified, the new elements are initialized as copies of val,
  // otherwise, they are value-initialized.
  void resize(size_t n, V val = V{}) {
    if (n > sz) {
      List l(n - sz, val);
      splice(nullptr, l);
    } else if (n < sz) {
      Item *fird = head;

      for (size_t i = 0; i < n; i++)
        fird = fird->next;
      erase(fird, nullptr);
    }
  }

  // Transfers elements from l into the container, inserting them at
  // position(pos).This effectively inserts those elements into the container
  // and removes them from l, altering the sizes of both containers. The
  // operation does not involve the construction or destruction of any element.
  void splice(Item *pos, List &l) {
    if (pos == head)
      head = l.head;
    else {
      pos->prev->next = l.head;
      l.head->prev = pos->prev;
    }

    if (pos == nullptr)
      tail = l.tail;
    else {
      l.tail->next = pos;
      pos->prev = l.tail;
    }
    sz += l.sz;
    l.sz = 0;
    l.head = nullptr;
    l.tail = nullptr;
  }
  // Removes from the container all the elements that compare equal to ele. This
  // calls the destructor of these objects and reduces the container size by the
  // number of elements removed.
  // inefficient implementation
  void remove(V ele) {
    for (Item *p = head; p != nullptr;)
      if (p->val == ele)
        p = erase(p, p->next);
      else
        p = p->next;
  }
};
} // namespace Nostd

#endif
