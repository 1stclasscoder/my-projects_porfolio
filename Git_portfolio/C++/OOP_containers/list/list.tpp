#include "list.h"

namespace S21 {

template <typename T>
list<T>::list() : list_n() {}

template <typename T>
list<T>::list(size_type n) {
  if (n > 0) {
    for (size_type i = 0; i < n; ++i) {
      list_n.push_front(value_type());
    }
  }
}

template <typename T>
list<T>::list(std::initializer_list<value_type> const& items) : list_n(items) {}

template <typename T>
list<T>::list(const list& l) : list_n(l.list_n) {}

template <typename T>
list<T>::list(list&& l) : list_n(l.list_n) {}

template <typename T>
list<T>::~list() {}

template <typename T>
typename list<T>::size_type list<T>::size() {
  return list_n.size();
}

template <typename T>
bool list<T>::empty() {
  return list_n.empty();
}

template <typename T>
typename list<T>::size_type list<T>::max_size() {
  return pow(2, (64 - log(sizeof(T)) / log(2))) - 1;
}

template <typename T>
void list<T>::clear() {
  list_n.clean_list();
}

template <typename T>
void list<T>::push_back(const_reference value) {
  list_n.push_back(value);
}

template <typename T>
void list<T>::pop_back() {
  list_n.pop_back();
}

template <typename T>
void list<T>::push_front(const_reference value) {
  list_n.push_front(value);
}

template <typename T>
void list<T>::pop_front() {
  list_n.pop_front();
}
template <typename T>
void list<T>::swap(list& other) {
  list_n.swap(other.list_n);
}

template <typename T>
typename list<T>::iterator list<T>::begin() {
  return iterator(list_n.get_head());
}

template <typename T>
typename list<T>::iterator list<T>::end() {
  return iterator(list_n.get_tail());
}

template <typename T>
typename list<T>::iterator list<T>::insert(iterator pos,
                                           const_reference value) {
  // if (pos == this->begin()){
  //       this->push_front(value);
  //       pos = list_n.get_head();
  // }
  // else
  if (pos == this->end()) {
    this->push_back(value);
    pos = list_n.get_tail();
  } else {
    return iterator(list_n.insert(pos.get_node(), value));
  }
  return pos;
}

template <typename T>
void list<T>::erase(iterator pos) {
  if (pos == this->begin()) {
    this->pop_front();
  } else if (pos.get_node() == list_n.get_tail()) {
    this->pop_back();
  } else if (pos.get_node() == nullptr) {
  } else {
    list_n.erase(pos.get_node());
  }
}

template <typename T>
void list<T>::splice(const_iterator pos, list& other) {
  if (!other.empty()) {
    for (iterator k = other.begin(); k != other.end(); ++k) {
      this->insert(pos, *k);
    }
  }
}

template <typename T>
void list<T>::unique() {
  if (!this->empty()) {
    for (auto i = this->begin(); i != this->end();) {
      auto j = i;
      j++;
      if (i.get_node() == nullptr) {
        return;
      } else if (*i == *j) {
        erase(j);
      } else {
        i++;
      }
    }
  }
}
template <typename T>
void list<T>::reverse() {
  list_n.reverse();
}

template <typename T>
void list<T>::sort() {
  if (size() <= 1) return;
  list<T> s;
  T buf;
  for (auto i = begin(); i != end(); i++) {
    buf = *i;
    for (auto j = i; j != end(); j++) {
      if (buf > *j) {
        buf = *j;
      }
    }
    s.push_back(buf);
  }
  this->list_n = s.list_n;
}

template <class T>
void list<T>::merge(list& other) {
  if (this != &other) {
    auto iter_1 = begin();
    auto iter_2 = other.begin();
    while (!other.empty()) {
      if (this->empty()) {
        insert(iter_1, *iter_2);
        other.erase(iter_2);
        ++iter_2;
      } else {
        if (iter_1 == end() || *iter_2 < *iter_1) {
          insert(iter_1, *iter_2);
          other.erase(iter_2);
          ++iter_2;
        } else {
          ++iter_1;
        }
      }
    }
  }
}

}  // namespace S21
