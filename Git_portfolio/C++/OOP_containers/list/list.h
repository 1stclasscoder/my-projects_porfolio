#ifndef S21_LIST_STRUCT
#define S21_LIST_STRUCT

#include <iostream>
#include <limits>

#include "../struct_list/iterators.h"

namespace S21 {
template <typename T>
class list {
  friend class node<T>;
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = iterator_l<T>;
  using const_iterator = constiterator_l<T>;
  using size_type = size_t;

 public:
  list();
  list(size_type n);
  list(std::initializer_list<value_type> const &items);
  list(const list &l);
  list(list &&l);
  ~list();

  list<T> operator=(list &&l);

  iterator begin();
  iterator end();

  bool empty();
  size_type size();
  size_type max_size();

  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void push_front(const_reference value);
  void pop_front();
  void swap(list &other);
  void merge(list &other);
  void splice(const_iterator pos, list &other);
  void reverse();
  void unique();
  void sort();

  value_type front() { return list_n.front(); }
  value_type back() { return list_n.back(); }

 private:
  node_list<T> list_n;
};
}  // namespace S21
#include "list.tpp"

#endif