#ifndef S21_QUEUE_STRUCT
#define S21_QUEUE_STRUCT

#include <iostream>

#include "../struct_list/iterators.h"

namespace S21 {
template <typename T>
class queue {
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

 public:
  queue();
  queue(std::initializer_list<value_type> const &items);
  queue(const queue &q);
  queue(queue &&q);
  ~queue();

  queue &operator=(const queue &q);
  queue &operator=(queue &&q);

  value_type front();
  value_type back();

  bool empty();
  size_type size();

  void push(const_reference value);
  void pop();
  void swap(queue &other);

 private:
  node_list<T> queue_n;
};
}  // namespace S21
#include "queue.tpp"

#endif