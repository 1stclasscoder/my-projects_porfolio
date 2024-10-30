#ifndef S21_NODE_ITERATORS_LIST_TPP
#define S21_NODE_ITERATORS_LIST_TPP

#include <iostream>

#include "./iterators.h"

namespace S21 {
template <typename T>
iterator_l<T>::iterator_l(node<T> *nod) : node_(nod) {}
template <typename T>
iterator_l<T>::iterator_l(node<T> *nod, node<T> *node_last)
    : node_(nod), node_prev_(node_last) {}
template <typename T>
iterator_l<T>::~iterator_l() {}

template <typename T>
iterator_l<T> &iterator_l<T>::operator++() {
  if (node_->next != nullptr) {
    node_prev_ = node_;
    node_ = node_->next;
  }
  return *this;
}
template <typename T>
iterator_l<T> iterator_l<T>::operator++(int) {
  iterator_l<T> iter = *this;
  if (node_->next != nullptr) {
    node_prev_ = node_;
    node_ = node_->next;
  }
  return iter;
}

template <typename T>
iterator_l<T> &iterator_l<T>::operator--() {
  if (node_->prev != nullptr) {
    node_ = node_->prev;
    node_prev_ = node_->prev;
  }
  return *this;
}

template <typename T>
iterator_l<T> iterator_l<T>::operator--(int) {
  iterator_l<T> iter = *this;
  if (node_->prev != nullptr) {
    node_ = node_->prev;
    node_prev_ = node_->prev;
  }
  return iter;
}
template <typename T>
typename iterator_l<T>::reference iterator_l<T>::operator*() const {
  return node_->value;
}

template <typename T>
typename iterator_l<T>::pointer iterator_l<T>::operator->() const {
  return &node_->value;
}
template <typename T>
bool iterator_l<T>::operator==(const iterator_l &other) const {
  return node_ == other.node_;
}
template <typename T>
bool iterator_l<T>::operator!=(const iterator_l &other) const {
  return node_ != other.node_;
}

template <typename T>
bool iterator_l<T>::operator>(const iterator_l &other) const {
  return node_ > other.node_;
}

template <typename T>
bool iterator_l<T>::operator<(const iterator_l &other) const {
  return node_ < other.node_;
}

template <typename T>
bool iterator_l<T>::operator>=(const iterator_l &other) const {
  return node_ >= other.node_;
}

template <typename T>
bool iterator_l<T>::operator<=(const iterator_l &other) const {
  return node_ <= other.node_;
}

template <typename T>
iterator_l<T> iterator_l<T>::operator+(const int value) {
  iterator_l buf = *this;
  for (int i = 0; i < value; i++) {
    buf++;
  }
  return buf;
}

};  // namespace S21
#endif