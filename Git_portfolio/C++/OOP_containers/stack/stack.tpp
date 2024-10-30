#include "stack.h"

namespace S21 {

template <typename T>
stack<T>::stack() : stack_n() {}

template <typename T>
stack<T>::stack(std::initializer_list<value_type> const &items)
    : stack_n(items) {}

template <typename T>
stack<T>::stack(const stack &s) : stack_n(s.stack_n) {}

template <typename T>
stack<T>::stack(stack &&s) : stack_n(std::move(s.stack_n)) {}

template <typename T>
stack<T>::~stack() {}

template <typename T>
stack<T> &stack<T>::operator=(stack &&s) {
  if (this != &s) {
    stack_n = std::move(s.stack_n);
  }
  return *this;
}

template <typename T>
stack<T> &stack<T>::operator=(const stack &s) {
  if (this != &s) {
    stack_n = std::move(s.stack_n);
  }
  return *this;
}

template <typename T>
typename stack<T>::value_type stack<T>::top() {
  return stack_n.back();
}

template <typename T>
bool stack<T>::empty() {
  return stack_n.empty();
}

template <typename T>
typename stack<T>::size_type stack<T>::size() {
  return stack_n.size();
}

template <typename T>
void stack<T>::push(const_reference value) {
  return stack_n.push_back(value);
}
template <typename T>
void stack<T>::pop() {
  return stack_n.pop_back();
}

template <typename T>
void stack<T>::swap(stack &other) {
  return stack_n.swap(other.stack_n);
}
}  // namespace S21
