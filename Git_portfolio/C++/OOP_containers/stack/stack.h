#ifndef S21_STACK_STRUCT
#define S21_STACK_STRUCT

#include <iostream>

#include "../struct_list/iterators.h"

namespace S21 {
template <typename T>
class stack {
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

 public:
  stack();
  stack(std::initializer_list<value_type> const &items);
  stack(const stack &s);
  stack(stack &&s);
  ~stack();

  stack &operator=(const stack &s);
  stack &operator=(stack &&s);

  value_type top();

  bool empty();
  size_type size();

  void push(const_reference value);
  void pop();
  void swap(stack &other);

 private:
  node_list<T> stack_n;
};
}  // namespace S21
#include "stack.tpp"

#endif