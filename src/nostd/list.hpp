#ifndef NOSTD_LIST_HPP
#define NOSTD_LIST_HPP

#include <iterator>
#include <stddef.h>
#include <stdexcept>

namespace Nostd {
// Lists are sequence containers that allow constant time insert and erase
// operations anywhere within the sequence, and iteration in both directions.
template <typename V> class List {
public:
  struct Item {
    V val;
    Item *next, *prev;
    List<V> *list;
  };

  struct iterator : public std::iterator<std::bidirectional_iterator_tag, V> {
    Item *item = nullptr;
    bool end = false;

    iterator() {}
    iterator(const iterator &it) { *this = it; }

    iterator &operator=(const iterator &it) {
      item = it.item;
      end = it.end;
      return *this;
    }

    bool operator==(iterator it) { return item == it.item && end == it.end; }
    bool operator!=(iterator it) { return !(*this == it); }

    V &operator*() { return item->val; }
    V *operator->() { return &item->val; }
    iterator &operator++() {
      if (item == item->list->tail)
        end = true;
      else
        item = item->next;
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
      else
        item = item->prev;
      return *this;
    }
    iterator operator--(int) {
      iterator backup = *this;
      --*this;
      return backup;
    }
  };
  using reverse_iterator = std::reverse_iterator<iterator>;
  using const_iterator = const iterator;
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
      Item *x = new Item;
      x->next = nullptr;
      x->prev = tail;
      x->list = this;
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
      x->list = this;
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
    erase(head, nullptr);
    sz = l.sz;
    head = l.head;
    tail = l->tail;
    l.head = nullptr;
    l->tail = nullptr;

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
    erase(head, nullptr);
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
      if (p == l->tail) {
        tail = x;
        x->next = nullptr;
      }
      prev = x;
    }
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
    x->list = this;
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
    x->list = this;
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
    for (Item *p = l.head; p != nullptr; p = p->next)
      p->list = this;

    if (pos == head)
      head = l.head;
    else {
      pos->prev->next = l.head;
      l.head->prev = pos->prev;
    }

    if (pos == nullptr)
      tail = l->tail;
    else {
      l->tail->next = pos;
      pos->prev = l->tail;
    }
    sz += l.sz;
    l.sz = 0;
    l.head = nullptr;
    l->tail = nullptr;
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
  iterator begin() {
    iterator p;
    p.item = head;
    return p;
  }
  const_iterator begin() const {
    iterator p;
    p.item = head;
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
  reverse_iterator rbegin() { return reverse_iterator(--end()); }
  reverse_iterator rend() { return reverse_iterator(--begin()); }
  const_iterator cbegin() const { return begin(); }
  const_iterator cend() const { return end(); }
  const_reverse_iterator crbegin() const {
    iterator it = end();
    return const_reverse_iterator(--it);
  }
  const_reverse_iterator crend() const {
    iterator it = end();
    return const_reverse_iterator(--it);
  }
};
} // namespace Nostd

#endif
