#include "./S21_set.h"
namespace S21 {

template <typename T>
set<T>::set() : tree_set() {}

template <typename T>
set<T>::set(const set &other) : tree_set(other.get_tree()) {}

template <typename T>
set<T>::set(std::initializer_list<value_type> const &keys) : tree_set() {
  for (auto k = keys.begin(); k != keys.end(); k++) {
    this->insert(*k);
  }
}

template <typename T>
set<T> &set<T>::operator=(set<T> &&other) {
  if (this != &other) {
    tree_set = std::move(other.tree_set);
  }
  return *this;
}

template <typename T>
bool set<T>::empty() {
  bool buf = false;
  if (this->tree_set.getroot() == nullptr ||
      this->tree_set.getroot()->size == 0) {
    buf = true;
  }
  return buf;
}

template <typename T>
typename set<T>::iterator set<T>::begin() {
  tree_node<T, T> *buf_tree = tree_set.getroot();
  if (buf_tree == nullptr) {
    return iterator(nullptr);
  } else {
    while (buf_tree->left != nullptr) {
      buf_tree = buf_tree->left;
    }
    return iterator(buf_tree);
  }
}

template <typename T>
typename set<T>::iterator set<T>::end() {
  return iterator(nullptr, tree_set.getroot());
}

template <typename T>
const AVL_tree<T, T> &set<T>::get_tree() const {
  return tree_set;
}

template <typename T>
void set<T>::swap(set<T> &other) {
  tree_set.swap_avl(other.tree_set);
}

template <typename T>
typename set<T>::size_type set<T>::size() {
  size_type buf = 0;
  if (tree_set.getroot() != nullptr) {
    buf = size_type(tree_set.getroot()->size);
  }
  return buf;
}

template <typename T>
void set<T>::erase(set<T>::iterator del_part) {
  if (del_part != nullptr) {
    tree_set.delete_key(*del_part);
  }
}

template <typename T>
typename set<T>::iterator set<T>::contains(const T &key) {
  return iterator(tree_set.search(key));
}

template <typename T>
void set<T>::clear() {
  if (tree_set.getroot() != nullptr) {
    tree_set.delete_class(tree_set.getroot());
  }
}

template <typename T>
void set<T>::merge(set &other) {
  if (this != &other) {
    for (auto k = other.begin(); k != other.end(); ++k) {
      insert(*k);
    }
    other.clear();
  }
}

template <typename T>
std::pair<typename set<T>::iterator, bool> set<T>::insert(const T &value) {
  tree_set.insert_avl(value);
  if (tree_set.get_insert()) {
    return std::make_pair(find(value), true);
  } else {
    return std::make_pair(find(value), false);
  }
}

template <typename T>
typename set<T>::size_type set<T>::max_size() {
  return pow(2, (64 - log(sizeof(T)) / log(2))) - 1;
}

template <typename T>
typename set<T>::iterator set<T>::find(const T &key) {
  return iterator(tree_set.search(key));
}

}  // namespace S21