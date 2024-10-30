#include "queue.h"

namespace S21 {
template <typename T>
queue<T>::queue() : queue_n() {}
template <typename T>
queue<T>::queue(std::initializer_list<value_type> const &items)
    : queue_n(items) {}
template <typename T>
queue<T>::queue(const queue &q) : queue_n(q.queue_n) {}
template <typename T>
queue<T>::queue(queue &&q) : queue_n(std::move(q.queue_n)) {}
template <typename T>
queue<T>::~queue() {}

template <typename T>
queue<T> &queue<T>::operator=(const queue &q) {
  if (this != &q) {
    queue_n = std::move(q.queue_n);
  }
  return *this;
}

template <typename T>
queue<T> &queue<T>::operator=(queue &&q) {
  if (this != &q) {
    queue_n = std::move(q.queue_n);
  }
  return *this;
}

template <typename T>
typename queue<T>::value_type queue<T>::front() {
  return queue_n.front();
}

template <typename T>
typename queue<T>::value_type queue<T>::back() {
  return queue_n.back();
}
template <typename T>
bool queue<T>::empty() {
  return queue_n.empty();
}

template <typename T>
typename queue<T>::size_type queue<T>::size() {
  return queue_n.size();
}

template <typename T>
void queue<T>::push(const_reference value) {
  queue_n.push_back(value);
}

template <typename T>
void queue<T>::pop() {
  queue_n.pop_front();
}

template <typename T>
void queue<T>::swap(queue &other) {
  queue_n.swap(other.queue_n);
}
}  // namespace S21
