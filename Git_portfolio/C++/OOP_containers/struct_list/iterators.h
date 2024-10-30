#ifndef S21_NODE_ITERATORS_LIST
#define S21_NODE_ITERATORS_LIST

#include <iostream>

#include "node_struct.h"

namespace S21 {
template <typename T>
class iterator_l {
 public:
  using key_type = T;
  using reference = T &;
  using const_reference = const T &;
  using pointer = T *;
  iterator_l(node<T> *nod = nullptr);
  iterator_l(node<T> *nod, node<T> *node_last);
  ~iterator_l();

  iterator_l operator+(const int value);
  iterator_l<T> &operator++();
  iterator_l<T> operator++(int);
  iterator_l &operator--();
  iterator_l operator--(int);
  reference operator*() const;
  pointer operator->() const;

  bool operator==(const iterator_l &other) const;
  bool operator!=(const iterator_l &other) const;
  bool operator>(const iterator_l &other) const;
  bool operator<(const iterator_l &other) const;
  bool operator>=(const iterator_l &other) const;
  bool operator<=(const iterator_l &other) const;

  node<T> *get_node() { return node_; }

 protected:
  node<T> *node_;
  node<T> *node_prev_;
};

template <typename T>
class constiterator_l : public iterator_l<const T> {
 public:
  using iterator_l<const T>::iterator;

  using typename iterator_l<const T>::key_type;
  using typename iterator_l<const T>::reference;
  using typename iterator_l<const T>::const_reference;
  using typename iterator_l<const T>::pointer;
};
}  // namespace S21
#include "./iterators.tpp"
#endif