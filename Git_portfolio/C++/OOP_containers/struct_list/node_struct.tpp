#include "node_struct.h"

namespace S21 {
template <typename T>
node_list<T>::node_list() : list_un() {}

template <typename T>
node_list<T>::node_list(std::initializer_list<value_type> const &items) {
  for (auto i = items.begin(); i != items.end(); ++i) {
    push_back(*i);
  }
}

template <typename T>
node_list<T>::node_list(const node_list &other) {
  node<T> *buf = other.list_un.head;
  while (buf) {
    push_back(buf->value);
    buf = buf->next;
  }
}

template <typename T>
node_list<T>::node_list(node_list &&other) {
  list_un.head = other.list_un.head;
  list_un.size = other.list_un.size;
  list_un.tail = other.list_un.tail;
  other.list_un.head = nullptr;
  other.list_un.tail = nullptr;
  other.list_un.size = 0;
}
template <typename T>
node_list<T>::~node_list() {
  clean_list();
}

template <typename T>
void node_list<T>::clean_list() {
  while (!empty()) {
    pop_front();
  }
}

template <typename T>
typename node_list<T>::value_type node_list<T>::front() {
  return list_un.head->value;
}

template <typename T>
typename node_list<T>::value_type node_list<T>::back() {
  return list_un.tail->value;
}

template <typename T>
void node_list<T>::push_back(const_reference value) {
  node<T> *buf = new node<T>(value);
  buf->next = nullptr;
  buf->prev = list_un.tail;
  if (list_un.tail) {
    list_un.tail->next = buf;
  }
  list_un.tail = buf;
  if (list_un.head == nullptr) {
    list_un.head = buf;
  }
  list_un.size++;
}

template <typename T>
void node_list<T>::swap(node_list &other) {
  std::swap(list_un.head, other.list_un.head);
  std::swap(list_un.size, other.list_un.size);
  std::swap(list_un.tail, other.list_un.tail);
}

template <typename T>
bool node_list<T>::empty() {
  return list_un.head == nullptr;
}

template <typename T>
void node_list<T>::pop_front() {
  if (list_un.head) {
    list_un.head = list_un.head->next;
    if (list_un.head) {
      list_un.head->prev = nullptr;
    } else {
      list_un.tail = nullptr;
    }
    --list_un.size;
  }
}

template <typename T>
node_list<T> &node_list<T>::operator=(const node_list &other) {
  if (this != &other) {
    while (!empty()) {
      pop_front();
    }
    node<T> *buf = other.list_un.head;
    while (buf) {
      push_back(buf->value);
      buf = buf->next;
    }
  }
  return *this;
}

template <typename T>
node_list<T> &node_list<T>::operator=(node_list &other) noexcept {
  if (this != &other) {
    while (!empty()) {
      pop_front();
    }
    list_un.head = other.list_un.head;
    list_un.size = other.list_un.size;
    list_un.tail = other.list_un.tail;
    other.list_un.head = nullptr;
    other.list_un.tail = nullptr;
    other.list_un.size = 0;
  }
  return *this;
}

template <typename T>
typename node_list<T>::size_type node_list<T>::size() {
  return list_un.size;
}

template <typename T>
void node_list<T>::pop_back() {
  if (list_un.tail != nullptr) {
    node<T> *buf = list_un.tail;
    list_un.tail = list_un.tail->prev;
    if (list_un.tail) {
      list_un.tail->next = nullptr;
    } else {
      list_un.head = nullptr;
    }
    delete buf;
    list_un.size--;
  }
}

template <typename T>
void node_list<T>::push_front(const_reference value) {
  node<T> *buf = new node<T>(value);
  buf->next = list_un.head;
  buf->prev = nullptr;
  if (list_un.head) {
    list_un.head->prev = buf;
  }
  list_un.head = buf;
  if (list_un.tail == nullptr) {
    list_un.head = buf;
  }
  list_un.size++;
}

template <typename T>
node<T> *node_list<T>::insert(node<T> *A, value_type value) {
  node<T> *blank = new node<T>(value);
  blank->prev = A;
  blank->next = A->next;
  A->next = blank;
  this->list_un.size++;
  return blank;
}

template <typename T>
void node_list<T>::erase(node<T> *A) {
  node<T> *node = A;
  node->prev->next = node->next;
  node->next->prev = node->prev;
  delete node;
  this->list_un.size--;
}

template <typename T>
void node_list<T>::reverse() {
  if (this->list_un.size > 1) {
    node<T> *node = this->list_un.head;
    for (size_type i = 0; i < this->list_un.size; ++i) {
      std::swap(node->prev, node->next);
      node = node->prev;
    }
    std::swap(this->list_un.head, this->list_un.tail);
  }
}
}  // namespace S21