#ifndef S21_NODE_STRUCT
#define S21_NODE_STRUCT

#include <iostream>

namespace S21 {
template <typename T>
class node {
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

 public:
  mutable value_type value;
  node<T> *next;
  node<T> *prev;
  node(value_type value_ = value_type(), node *next_ = nullptr,
       node *prev_ = nullptr)
      : value(value_), next(next_), prev(prev_) {}
};
template <typename T>
class un_list {
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

 public:
  node<T> *head;
  node<T> *tail;
  size_t size;
  un_list(node<T> *head_ = nullptr, node<T> *tail_ = nullptr, size_t size_ = 0)
      : head(head_), tail(tail_), size(size_) {}
};

template <typename T>
class node_list {
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

 public:
  node_list();
  node_list(std::initializer_list<value_type> const &items);
  node_list(const node_list &other);
  node_list(node_list &&other);
  ~node_list();

  node_list<T> &operator=(const node_list &other);
  node_list<T> &operator=(node_list &other) noexcept;

  void push_back(const_reference value);
  void push_front(const_reference value);
  void pop_front();
  void pop_back();

  void swap(node_list &other);
  bool empty();
  size_type size();
  void clean_list();

  value_type front();
  value_type back();

  node<T> *get_head() const { return list_un.head; }

  node<T> *get_tail() const { return list_un.tail; }

  node<T> *insert(node<T> *A, value_type value);
  void erase(node<T> *A);

  void reverse();

  void sort();
  node<T> *merge_sort(node<T> *head);
  node<T> *Merge(node<T> *left, node<T> *right);
  node<T> *GetMiddle(node<T> *head);

 protected:
  un_list<T> list_un;
};
}  // namespace S21
#include "node_struct.tpp"
#endif