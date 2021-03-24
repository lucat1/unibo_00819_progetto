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
    item* next;
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
      if (i == 0)
        head = x;

      if (tail != nullptr)
        tail->next = x;
      tail = x;
    }
  }

  bool empty() { return sz == 0; }

  size_t size() { return sz; }

  V& front() { return head->val; }

  V& back() { return tail->val; }

  void push_front(V ele) {
    item* x = new item;
    x->val = ele;
    x->next = head;
    head = x;
    if (tail == nullptr)
      tail = x;
  }

  void push_back(V ele) {
    item* x = new item;
    x->val = ele;
    x->next = nullptr;
    if (tail == nullptr)
      head = x;
    else
      tail->next = x;
    tail = x;
  }
};
}  // namespace Nostd

#endif
