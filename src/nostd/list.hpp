#ifndef NOSTD_LIST_HPP
#define NOSTD_LIST_HPP

#include <stddef.h>
#include <stdexcept>

namespace Nostd {

template <typename V>
class List {
 protected:
  struct item {
    V val;
    item *next, *prev;
  };
  size_t sz;
  item *head, *tail;

 public:
  List() {
    sz = 0;
    head = nullptr;
    tail = nullptr;
  }
  List(size_t size) {
    sz = size;
    for (size_t i = 0; i < sz; i++) {
      item* x = new item;
      x->next = nullptr;
      x->prev = tail;
      if (i == 0)
        head = x;
      if (tail != nullptr)
        tail->next = x;
      tail = x;
    }
  }
  List(size_t size, V ele) {
    sz = size;
    for (size_t i = 0; i < sz; i++) {
      item* x = new item;
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
  // previous list in an undefined state
  List(List&& list) {
    sz = list.sz;
    head = list.head;
    tail = list.tail;
    list.head = nullptr;
    list.tail = nullptr;
  }
  // Constructs a new list by copying all items from another list
  List(List& list) {
    sz = list.sz;
    item* prev = nullptr;

    for (item* it = list.head; it != nullptr; it = it->next) {
      item* x = new item;
      x->val = it->val;

      if (prev == nullptr)
        head = x;
      prev = x;
    }

    tail = prev;
    tail->next = nullptr;
  }

  bool empty() { return sz == 0; }
  size_t size() { return sz; }
  V& front() { return head->val; }
  V& back() { return tail->val; }

  void push_front(V ele) {
    item* x = new item;
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
  void push_back(V ele) {
    item* x = new item;
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
  item* erase(item* first, item* last) {
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

    for (item* p = first; p != last;) {
      item* del = p;
      p = p->next;
      delete del;
      sz--;
    }
    return last;
  }
  void pop_front() {
    if (head != nullptr)
      erase(head, head->next);
  }
  void pop_back() { erase(tail, nullptr); }
  void resize(size_t n, V val) {
    if (n > sz) {
      List l(n - sz, val);
      splice(nullptr, l);
    } else if (n < sz) {
      item* fird = head;
      for (size_t i = 0; i < n; i++)
        fird = fird->next;
      erase(fird, nullptr);
    }
  }
  void splice(item* pos, List& l) {
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
  // implementazione inefficiente
  void remove(V ele) {
    for (item* p = head; p != nullptr;)
      if (p->val == ele)
        p = erase(p, p->next);
      else
        p = p->next;
  }
};
}  // namespace Nostd

#endif
